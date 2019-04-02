#pragma once


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

auto const annotation_text
   = x3::rule<struct annotation_text_id, std::string> {"annotation_text"}
   = x3::lexeme[*(x3::char_ - (lit("**>") | lit("@"))) ];

auto const fannotation
   = x3::rule<struct fannotation_id, ast::FAnnotation> { "fannotation" }
   = lit("@") >> identifier >> ":" >> annotation_text;

auto const fannotation_block
   = x3::rule<struct fannotation_block_id, ast::FAnnotationBlock> { "fannotation_block" }
   = lit("<**") >> *fannotation >> "**>";

auto const polymorphic_clause
   = x3::rule<struct polymorphic_id, string> { "polymorphic_clause" }
   = lit("polymorphic") >> x3::attr(string())
                        | lit("extends") >> known_type;

auto const array_braces = lit("[") >> lit("]") >> x3::attr(true);

auto const struct_member
   = x3::rule<struct struct_member_id, ast::FStructMember> { "struct_member" }
   = known_type > -array_braces > identifier;

auto const fstruct
   = x3::rule<struct fstruct_id, ast::FStruct> { "fstruct" }
   =  -fannotation_block >> "struct" > identifier >> -polymorphic_clause > "{" >> *(struct_member) > "}";

auto const enum_member
   = x3::rule<struct enum_member_id, ast::FEnum_Member> { "enum_member" }
   = identifier >> -("=" > int_);

auto const fenum
   = x3::rule<struct fenum_id, ast::FEnum> { "fenum" }
   = -fannotation_block >> "enumeration" > identifier > "{" >> *(enum_member) > "}";

auto const ftypedef
   = x3::rule<struct ftypedef_id, ast::FTypeDef> { "ftypedef" }
   = -fannotation_block >> "typedef" > identifier > "is" > known_type;

auto const version
   = x3::rule<struct version_id, ast::FVersion> { "version" }
   = lit("version") > "{" > lit("major") > int_ > lit("minor") > int_ > "}";

auto const ftype
   = x3::rule<struct ftype_id, ast::FType> { "ftype" }
   = fstruct | ftypedef | fenum;

auto const types_set
   = x3::rule<struct types_set_id, vector<ast::FType>> { "types_set" }
   = *(ftype[add_type]);

auto const ftypecollection
   = x3::rule<struct ftypecollection_id, ast::FTypeCollection> { "type_collection" }
   = lit("typeCollection") > identifier > "{" >> -(version) >> types_set > "}";

auto const fmodel
   = x3::rule<struct fmodel_id, ast::FModel> { "fmodel" }
   = package >> *ftypecollection;
struct fmodel_id : error_handler, x3::annotate_on_success {};

}
