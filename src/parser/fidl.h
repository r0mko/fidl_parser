#pragma once

#include <boost/spirit/home/x3.hpp>
#include <string>
#include <iostream>

#include "ast/ast.h"
#include "utils.h"

namespace fidl {

namespace x3 = boost::spirit::x3;
namespace ascii = boost::spirit::x3::ascii;

using namespace std;

using x3::int_;
using x3::lit;
using x3::double_;
using x3::lexeme;
using x3::_val;
using x3::_attr;

x3::rule<class identifier_id, string> const identifier { "identifier" };
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

auto const identifier_def = x3::raw[lexeme[(x3::alpha | '_') >> *(x3::alnum | '_')]];

static struct known_type_parser : x3::symbols<string>
{
    known_type_parser();
} known_type;

// FIXME: remove. This is a helper function for debugging purposes.
template<typename T>
void introspect(T &ctx) {
    cout << "attr type: " << getTypeName(_attr(ctx)) << endl;
    cout << "val type: " << getTypeName(_val(ctx)) << endl;
};

auto add_type = [](auto &ctx)
{
    string name =_attr(ctx).getName();
    cout << "Added new type " << name << endl;
    known_type.add(name, name);
    _val(ctx).push_back(_attr(ctx));
};

auto const polymorphic_clause_def
    = lit("polymorphic") >> x3::attr(string())
    | lit("extends") >> known_type;

auto const array_braces = lit("[") >> lit("]") >> x3::attr(true);

auto const struct_member_def = known_type >> -array_braces >> identifier;
auto const fstruct_def =  -fannotation_block >> "struct" >> identifier >> -polymorphic_clause >> "{" >> *(struct_member) >> "}";

auto const enum_member_def = identifier >> -("=" >> int_);
auto const fenum_def = -fannotation_block >> "enumeration" >> identifier >> "{" >> *(enum_member) >> "}";

auto const ftypedef_def = -fannotation_block >> "typedef" >> identifier >> "is" >> known_type;

auto const version_def = lit("version") >> "{" >> lit("major") >> int_ >> lit("minor") >> int_ >> "}";
auto const ftype_def = fstruct | ftypedef | fenum;
auto const types_set_def = *(ftype[add_type]);
auto const ftypecollection_def = lit("typeCollection") >> identifier >> "{" >> -(version) >> types_set >> "}";

auto const annotation_text = x3::rule<class annotation_text_id, std::string>{} = x3::lexeme[*(x3::char_ - (lit("**>") | lit("@"))) ];
auto const fannotation_def = lit("@") >> identifier >> ":" >> annotation_text;
auto const fannotation_block_def = lit("<**") >> *fannotation >> "**>";

auto const fmodel_def = lit("package") >> x3::lexeme[identifier % "."] >> *ftypecollection;

auto const whitespace
    = x3::blank
    | x3::lexeme[ "//" >> *(x3::char_ - x3::eol) >> x3::eol ]
    | x3::eol;

BOOST_SPIRIT_DEFINE(
    identifier,
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
