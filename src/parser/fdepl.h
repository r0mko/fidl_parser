#pragma once

#include <boost/spirit/home/x3.hpp>
#include <string>
#include <iostream>

#include "ast/ast.h"
#include "utils.h"

namespace fdepl {

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

using identifier_type = string;
x3::rule<class identifier_id, identifier_type> const identifier { "identifier" };

using propvalue_type = x3::variant<bool, int64_t, double, identifier_type>;
x3::rule<class propvalue_id, propvalue_type> const propvalue { "propvalue" };
using property_type = pair<identifier_type, propvalue_type>;
x3::rule<class property_id, property_type> const property { "property" };
using propertyset_type = vector<property_type>;
x3::rule<class propertyset_id, propertyset_type> const propertyset { "propertyset" };

using fmember_type = pair<identifier_type, propertyset_type>;
x3::rule<class fmember_id, fmember_type> const fmember { "fmember" };

using fstrenum_type = pair<identifier_type, vector<fmember_type>>;
x3::rule<class fenum_id, fstrenum_type> const fenum { "fenum" };
x3::rule<class fstruct_id, fstrenum_type> const fstruct { "fstruct" };

using fqn_type = vector<identifier_type>;
x3::rule<class fqn_id, fqn_type> const fqn { "fqn" };

x3::rule<class import_id, identifier_type> const import { "import" };
using data_type = x3::variant<propertyset_type, fstrenum_type>;
using fdepl_define_type = tuple<fqn_type, fqn_type, vector<data_type>>;
x3::rule<class fdepl_define_id, fdepl_define_type> const fdepl_define { "fdepl_define" };

auto const whitespace
   = x3::blank
   | x3::lexeme[ "//" >> *(x3::char_ - x3::eol) >> x3::eol ]
   | x3::eol;

auto const identifier_def = x3::raw[lexeme[(x3::alpha | '_') >> *(x3::alnum | '_')]];
auto const propvalue_def = bool_ | int_ | double_ | identifier;
auto const property_def = identifier >> lit("=") >> propvalue;
auto const propertyset_def = *(-lit(",") >> property);
auto const fmember_def = identifier >> lit("{") >> propertyset >> lit("}");
auto const fenum_def = lit("enumeration") >> identifier >> "{" >> *(fmember) >> "}";
auto const fstruct_def = lit("struct") >> identifier >> "{" >> *(fmember) >> "}";
auto const fqn_def = identifier % ".";
auto const import_def = '"' >> lexeme[ identifier > lit("fidl") ] >> '"';
auto const fdepl_define_def =  lit("define") >> fqn >>
                               lit("for") >> lit("typeCollection") >> fqn >>
                               lit("{") >>
                               *( propertyset | fenum | fstruct) >>
                               lit("}");

BOOST_SPIRIT_DEFINE(
   identifier,
   propvalue,
   property,
   fmember,
   fenum,
   fstruct,
   fqn,
   import,
   fdepl_define);

}
