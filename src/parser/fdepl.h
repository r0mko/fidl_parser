#pragma once

#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <string>
#include <iostream>

#include "ast/ast.h"
#include "common.h"
#include "utils.h"

namespace franca {

namespace x3 = boost::spirit::x3;
namespace ascii = boost::spirit::x3::ascii;

using namespace std;

using x3::bool_;
using x3::int_;
using x3::lit;
using x3::double_;
using x3::lexeme;
using x3::_val;
using x3::_attr;

x3::rule<class property_id, ast::FDProperty> const fdproperty { "property" };
x3::rule<class propertyset_id, ast::FDPropertySet> const fdpropertyset { "propertyset" };
x3::rule<class fdenum_id, ast::FDEnumeration> const fdenum { "fdenum" };
x3::rule<class fdstruct_id, ast::FDStruct> const fdstruct { "fdstruct" };
x3::rule<class fdtypedef_id, ast::FDTypedef> const fdtypedef { "fdtypedef" };
x3::rule<class import_id, string> const import { "import" };
x3::rule<class fdtypes_id, ast::FDTypes> const fdtypes { "fdtypes" };
x3::rule<class fdmodel_id, ast::FDModel> const fdmodel { "fdmodel" };

auto const fdvalue
    = x3::rule<class fdvalue_id, ast::FDValue> { "propvalue" }
    = bool_ | int_ | double_ | identifier;

auto const fdproperty_def = identifier >> lit("=") >> fdvalue;
auto const fdpropertyset_def = fdproperty >> *(-lit(",") >> fdproperty);
auto const fdfield
    = x3::rule<class fmember_id, ast::FDField> { "fdmember" }
    = identifier >> lit("{") >> fdpropertyset >> lit("}");

auto const fdtypedef_def = lit("typedef") >> identifier >> '{' >> -fdpropertyset >> '}';
auto const fdenum_def = lit("enumeration") >> identifier >> '{' >> -fdpropertyset >> *(fdfield) >> '}';
auto const fdstruct_def = lit("struct") >> identifier >> '{' >> -fdpropertyset >> *(fdfield) >> '}';
auto const import_def = lit("import") >> lexeme['"' >> identifier >> lit(".fidl") >> '"'];  // x3::lexeme assumes no skip parser, i. e. no whitespace in between

auto const fdtypedefinition
    = x3::rule<class fdtypedefinition_id, ast::FDTypeDefinition> { "data" }
    = fdtypedef | fdenum | fdstruct;

auto const fdtypes_def = lit("define") >> fqn >> lit("for") >> lit("typeCollection") >> fqn
                                       >> "{" >> -fdpropertyset >> *fdtypedefinition >> "}";

auto const fdmodel_def = import >> *fdtypes;

}
