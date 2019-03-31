#ifndef PARSER_FIDL_H
#define PARSER_FIDL_H

#include <string>
#include <iostream>

#include "ast/ast.h"

#include "common.h"

namespace franca {

namespace x3 = boost::spirit::x3;

using namespace std;

using x3::int_;
using x3::lit;
using x3::double_;
using x3::lexeme;
using x3::_val;
using x3::bool_;
using x3::_attr;

x3::rule<class fstruct_id, ast::FStruct> const fstruct { "fstruct" };
x3::rule<class struct_member_id, ast::FStructMember> const struct_member { "struct_member" };
x3::rule<class polymorphic_clause, string> const polymorphic_clause { "polymorphic_clause" };
x3::rule<class ftypedef_id, ast::FTypeDef> const ftypedef { "ftypedef" };
x3::rule<class fenum_id, ast::FEnum> const fenum { "fenum" };
x3::rule<class enum_member_id, ast::FEnum_Member> const enum_member { "enum_member" };
x3::rule<class ftype_id, ast::FType> const ftype { "ftype" };
x3::rule<class version_id, ast::FVersion> const version { "version" };
x3::rule<class types_set_id, vector<ast::FType>> const types_set { "types_set" };
x3::rule<class ftypecollection_id, ast::FTypeCollection> const ftypecollection { "type_collection" };
x3::rule<class fannotation_id, ast::FAnnotation> const fannotation { "fannotation" };
x3::rule<class fannotation_block_id, ast::FAnnotationBlock> const fannotation_block { "fannotation_block" };
x3::rule<class fmodel_id, ast::FModel> const fmodel { "fmodel" };

auto const polymorphic_clause_def
= lit("polymorphic") >> x3::attr(string())
                        | lit("extends") >> known_type_parser::i();

auto const array_braces = lit("[") >> lit("]") >> x3::attr(true);

auto const struct_member_def = known_type_parser::i() >> -array_braces >> identifier;
auto const fstruct_def =  -fannotation_block >> "struct" >> identifier >> -polymorphic_clause >> "{" >> *(struct_member) >> "}";

auto const enum_member_def = identifier >> -("=" >> int_);
auto const fenum_def = -fannotation_block >> "enumeration" >> identifier >> "{" >> *(enum_member) >> "}";

auto const ftypedef_def = -fannotation_block >> "typedef" >> identifier >> "is" >> known_type_parser::i();

auto const version_def = lit("version") >> "{" >> lit("major") >> int_ >> lit("minor") >> int_ >> "}";
auto const ftype_def = fstruct | ftypedef | fenum;
auto const types_set_def = *(ftype[add_type]);
auto const ftypecollection_def = lit("typeCollection") >> identifier >> "{" >> -(version) >> types_set >> "}";

auto const annotation_text = x3::rule<class annotation_text_id, std::string>{} = x3::lexeme[*(x3::char_ - (lit("**>") | lit("@"))) ];
auto const fannotation_def = lit("@") >> identifier >> ":" >> annotation_text;
auto const fannotation_block_def = lit("<**") >> *fannotation >> "**>";

auto const fmodel_def = package >> *ftypecollection;

// FIXME: remove
using property_t = pair<string, int>;
auto const property = x3::rule<class property_id, property_t> {"property"} = identifier >> lit("=") >> int_;

auto const propertyset = x3::rule<class propertyset_id, vector<property_t>> {"propertyset"} =
        property >> *(-lit(",") >> property);

auto const field = x3::rule<class field_id, string> {"field"} =
    identifier >> lit("{") >> lit("}");
using structf_t = pair<vector<property_t>, vector<string>>;
auto const structf = x3::rule<class structf_id, structf_t> {"structf"}
    = lit("struct") >> "{" >> -propertyset >> *field >> "}";


BOOST_SPIRIT_DEFINE(
        polymorphic_clause,
        fannotation,
        fannotation_block,
        struct_member,
        fstruct,
        fenum,
        enum_member,
        ftypedef,
        ftype,
        version,
        types_set,
        ftypecollection,
        fmodel);
}

#endif
