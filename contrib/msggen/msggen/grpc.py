# A grpc model
from .model import ArrayField, Field, CompositeField, EnumField, PrimitiveField, Service
from typing import TextIO, List
from textwrap import indent, dedent
import re
import logging


typemap = {
    'boolean': 'bool',
    'hex': 'bytes',
    'msat': 'Amount',
    'number': 'sint64',
    'pubkey': 'bytes',
    'short_channel_id': 'string',
    'signature': 'bytes',
    'string': 'string',
    'txid': 'bytes',
    'u8': 'uint32',  # Yep, this is the smallest integer type in grpc...
    'u32': 'uint32',
    'u64': 'uint64',
    'u16': 'uint32',  # Yeah, I know...
    'integer': 'sint64',
}


# Manual overrides for some of the auto-generated types for paths
overrides = {
    # Truncate the tree here, it's a complex structure with identitcal
    # types
    'ListPeers.peers[].channels[].state_changes[]': None,
    'ListPeers.peers[].channels[].opener': "ChannelSide",
    'ListPeers.peers[].channels[].closer': "ChannelSide",
    'ListPeers.peers[].channels[].features[]': "string",
    'ListFunds.channels[].state': 'ChannelState',
}

method_name_overrides = {
    "Connect": "ConnectPeer",
}


class GrpcGenerator:
    """A generator that generates protobuf files.
    """

    def __init__(self, dest: TextIO):
        self.dest = dest
        self.logger = logging.getLogger("msggen.grpc.GrpcGenerator")

    def write(self, text: str, cleanup: bool = True) -> None:
        if cleanup:
            self.dest.write(dedent(text))
        else:
            self.dest.write(text)

    def gather_types(self, service):
        """Gather all types that might need to be defined.
        """

        def gather_subfields(field: Field) -> List[Field]:
            fields = [field]

            if isinstance(field, CompositeField):
                for f in field.fields:
                    fields.extend(gather_subfields(f))
            elif isinstance(field, ArrayField):
                fields = []
                fields.extend(gather_subfields(field.itemtype))

            return fields

        types = []
        for method in service.methods:
            types.extend([method.request, method.response])
            for field in method.request.fields:
                types.extend(gather_subfields(field))
            for field in method.response.fields:
                types.extend(gather_subfields(field))
        return types

    def generate_service(self, service: Service) -> None:
        self.write(f"""
        service {service.name} {{
        """)

        for method in service.methods:
            mname = method_name_overrides.get(method.name, method.name)
            self.write(
                f"	rpc {mname}({method.request.typename}) returns ({method.response.typename}) {{}}\n",
                cleanup=False,
            )

        self.write(f"""}}
        """)

    def generate_enum(self, e: EnumField, indent=0):
        self.logger.debug(f"Generating enum {e}")
        prefix = "\t" * indent
        self.write(f"{prefix}// {e.path}\n", False)
        self.write(f"{prefix}enum {e.typename} {{\n", False)

        for i, v in enumerate(e.variants):
            self.logger.debug(f"Generating enum variant {v}")
            self.write(f"{prefix}\t{v.normalized()} = {i};\n", False)

        self.write(f"""{prefix}}}\n""", False)

    def generate_message(self, message: CompositeField):
        if overrides.get(message.path, "") is None:
            return

        self.write(f"""
        message {message.typename} {{
        """)

        # Declare enums inline so they are scoped correctly in C++
        for i, f in enumerate(message.fields):
            if isinstance(f, EnumField) and f.path not in overrides.keys():
                self.generate_enum(f, indent=1)

        for i, f in enumerate(message.fields):
            if overrides.get(f.path, "") is None:
                continue

            opt = "optional " if not f.required else ""
            if isinstance(f, ArrayField):
                typename = typemap.get(f.itemtype.typename, f.itemtype.typename)
                if f.path in overrides:
                    typename = overrides[f.path]
                self.write(f"\trepeated {typename} {f.normalized()} = {i+1};\n", False)
            elif isinstance(f, PrimitiveField):
                typename = typemap.get(f.typename, f.typename)
                if f.path in overrides:
                    typename = overrides[f.path]
                self.write(f"\t{opt}{typename} {f.normalized()} = {i+1};\n", False)
            elif isinstance(f, EnumField):
                typename = f.typename
                if f.path in overrides:
                    typename = overrides[f.path]
                self.write(f"\t{opt}{typename} {f.normalized()} = {i+1};\n", False)

        self.write(f"""}}
        """)

    def generate(self, service: Service) -> None:
        """Generate the GRPC protobuf file and write to `dest`
        """
        self.write(f"""syntax = "proto3";\npackage cln;\n""")
        self.write("""
        // This file was automatically derived from the JSON-RPC schemas in
        // `doc/schemas`. Do not edit this file manually as it would get
        // overwritten.

        """)

        for i in service.includes:
            self.write(f"import \"{i}\";\n")

        self.generate_service(service)

        fields = self.gather_types(service)

        for message in [f for f in fields if isinstance(f, CompositeField)]:
            self.generate_message(message)


class GrpcConverterGenerator:
    def __init__(self, dest: TextIO):
        self.dest = dest
        self.logger = logging.getLogger("msggen.grpc.GrpcConversionGenerator")

    def generate_array(self, prefix, field: ArrayField):
        if isinstance(field.itemtype, CompositeField):
            self.generate_composite(prefix, field.itemtype)

    def generate_composite(self, prefix, field: CompositeField):
        """Generates the conversions from JSON-RPC to GRPC.
        """
        if overrides.get(field.path, "") is None:
            return

        # First pass: generate any sub-fields before we generate the
        # top-level field itself.
        for f in field.fields:
            if isinstance(f, ArrayField):
                self.generate_array(prefix, f)

        # And now we can convert the current field:
        self.write(f"""\
        #[allow(unused_variables)]
        impl From<&{prefix}::{field.typename}> for pb::{field.typename} {{
            fn from(c: &{prefix}::{field.typename}) -> Self {{
                Self {{
        """)

        for f in field.fields:
            if overrides.get(f.path, "") is None:
                continue

            name = f.normalized()
            if isinstance(f, ArrayField):
                self.write(f"{name}: c.{name}.iter().map(|s| s.into()).collect(),\n", numindent=3)

            elif isinstance(f, EnumField):
                if f.required:
                    self.write(f"{name}: c.{name} as i32,\n", numindent=3)
                else:
                    self.write(f"{name}: c.{name}.map(|v| v as i32),\n", numindent=3)

            elif isinstance(f, PrimitiveField):
                typ = f.typename + ("?" if not f.required else "")
                # We may need to reduce or increase the size of some
                # types, or have some conversion such as
                # hex-decoding. Also includes the `Some()` that grpc
                # requires for non-native types.
                rhs = {
                    'u8': f'c.{name}.into()',
                    'u16': f'c.{name}.into()',
                    'u16?': f'c.{name}.map(|v| v.into())',
                    'msat': f'Some(c.{name}.into())',
                    'msat?': f'c.{name}.map(|f| f.into())',
                    'pubkey': f'hex::decode(&c.{name}).unwrap()',
                    'pubkey?': f'c.{name}.as_ref().map(|v| hex::decode(&v).unwrap())',
                    'hex': f'hex::decode(&c.{name}).unwrap()',
                    'hex?': f'c.{name}.as_ref().map(|v| hex::decode(&v).unwrap())',
                    'txid': f'hex::decode(&c.{name}).unwrap()',
                    'txid?': f'c.{name}.as_ref().map(|v| hex::decode(&v).unwrap())',
                }.get(
                    typ,
                    f'c.{name}.clone()'  # default to just assignment
                )
                self.write(f"{name}: {rhs},\n", numindent=3)

        self.write(f"""\
                }}
            }}
        }}

        """)

    def generate_requests(self, service):
        for meth in service.methods:
            req = meth.request
            self.generate_composite("requests", req)

    def generate_responses(self, service):
        for meth in service.methods:
            res = meth.response
            self.generate_composite("responses", res)

    def generate(self, service: Service) -> None:
        self.write("""
        // This file was automatically derived from the JSON-RPC schemas in
        // `doc/schemas`. Do not edit this file manually as it would get
        // overwritten.

        use std::convert::From;
        #[allow(unused_imports)]
        use cln_rpc::model::{responses,requests};
        use crate::pb;

        """)

        self.generate_responses(service)

    def write(self, text: str, numindent: int = 0) -> None:
        raw = dedent(text)
        if numindent > 0:
            raw = indent(text, "    " * numindent)

        self.dest.write(raw)


class GrpcUnconverterGenerator(GrpcConverterGenerator):
    """Generator to generate the conversions from GRPC to JSON-RPC (for requests).
    """
    def generate(self, service: Service):
        self.generate_requests(service)

    def generate_composite(self, prefix, field: CompositeField) -> None:
        # First pass: generate any sub-fields before we generate the
        # top-level field itself.
        if overrides.get(field.path, "") is None:
            return

        for f in field.fields:
            if isinstance(f, ArrayField):
                self.generate_array(prefix, f)

        # And now we can convert the current field:
        self.write(f"""\
        #[allow(unused_variables)]
        impl From<&pb::{field.typename}> for {prefix}::{field.typename} {{
            fn from(c: &pb::{field.typename}) -> Self {{
                Self {{
        """)

        for f in field.fields:
            name = f.normalized()
            if isinstance(f, ArrayField):
                self.write(f"{name}: c.{name}.iter().map(|s| s.into()).collect(),\n", numindent=3)

            elif isinstance(f, EnumField):
                if f.required:
                    self.write(f"{name}: c.{name}.into(),\n", numindent=3)
                else:
                    self.write(f"{name}: c.{name}.map(|v| v.try_into().unwrap()),\n", numindent=3)
                pass
            elif isinstance(f, PrimitiveField):
                typ = f.typename + ("?" if not f.required else "")
                # We may need to reduce or increase the size of some
                # types, or have some conversion such as
                # hex-decoding. Also includes the `Some()` that grpc
                # requires for non-native types.
                rhs = {
                    'u16': f'c.{name} as u16',
                    'u16?': f'c.{name}.map(|v| v as u16)',
                    'hex': f'hex::encode(&c.{name})',
                    'hex?': f'c.{name}.clone().map(|v| hex::encode(v))',
                    'txid?': f'c.{name}.clone().map(|v| hex::encode(v))',
                    'pubkey': f'hex::encode(&c.{name})',
                    'pubkey?': f'c.{name}.clone().map(|v| hex::encode(v))',
                    'msat': f'c.{name}.as_ref().unwrap().into()'
                }.get(
                    typ,
                    f'c.{name}.clone()'  # default to just assignment
                )
                self.write(f"{name}: {rhs},\n", numindent=3)

        self.write(f"""\
                }}
            }}
        }}

        """)


class GrpcServerGenerator(GrpcConverterGenerator):
    def generate(self, service: Service) -> None:
        self.write(f"""\
        use crate::pb::node_server::Node;
        use crate::pb;
        use cln_rpc::{{Request, Response, ClnRpc}};
        use anyhow::Result;
        use std::path::{{Path, PathBuf}};
        use cln_rpc::model::requests;
        use log::debug;
        use crate::convert::*;
        use tonic::{{Code, Status}};

        #[derive(Clone)]
        pub struct Server
        {{
            rpc_path: PathBuf,
        }}

        impl Server
        {{
            pub async fn new(path: &Path) -> Result<Self>
            {{
                Ok(Self {{
                    rpc_path: path.to_path_buf(),
                }})
            }}
        }}

        #[tonic::async_trait]
        impl Node for Server
        {{
        """)

        for method in service.methods:
            mname = method_name_overrides.get(method.name, method.name)
            # Tonic will convert to snake-case, so we have to do it here too
            name = re.sub(r'(?<!^)(?=[A-Z])', '_', mname).lower()
            self.write(f"""\
            async fn {name}(
                &self,
                request: tonic::Request<pb::{method.request.typename}>,
            ) -> Result<tonic::Response<pb::{method.response.typename}>, tonic::Status> {{
                let req = request.into_inner();
                let req: requests::{method.request.typename} = (&req).into();
                debug!("Client asked for getinfo");
                let mut rpc = ClnRpc::new(&self.rpc_path)
                    .await
                    .map_err(|e| Status::new(Code::Internal, e.to_string()))?;
                let result = rpc.call(Request::{method.name}(req))
                    .await
                    .map_err(|e| Status::new(
                       Code::Unknown,
                       format!("Error calling method {method.name}: {{:?}}", e)))?;
                match result {{
                    Response::{method.name}(r) => Ok(
                        tonic::Response::new((&r).into())
                    ),
                    r => Err(Status::new(
                        Code::Internal,
                        format!(
                            "Unexpected result {{:?}} to method call {method.name}",
                            r
                        )
                    )),
                }}

            }}\n\n""", numindent=0)

        self.write(f"""\
        }}
        """, numindent=0)
