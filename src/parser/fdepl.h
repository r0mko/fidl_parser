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

using identifier_t = string;
x3::rule<class identifier_id, identifier_t> const identifier { "identifier" };

using propvalue_t = x3::variant<bool, int64_t, double, identifier_t>;
x3::rule<class propvalue_id, propvalue_t> const propvalue { "propvalue" };
using property_t = pair<identifier_t, propvalue_t>;
x3::rule<class property_id, property_t> const property { "property" };
using propertyset_t = vector<property_t>;
x3::rule<class propertyset_id, propertyset_t> const propertyset { "propertyset" };

using fmember_t = pair<identifier_t, propertyset_t>;
x3::rule<class fmember_id, fmember_t> const fmember { "fmember" };

using fstrenum_t = pair<identifier_t, vector<fmember_t>>;
x3::rule<class fenum_id, fstrenum_t> const fenum { "fenum" };
x3::rule<class fstruct_id, fstrenum_t> const fstruct { "fstruct" };

using fqn_t = vector<identifier_t>;
x3::rule<class fqn_id, fqn_t> const fqn { "fqn" };

x3::rule<class import_id, identifier_t> const import { "import" };
using data_t = x3::variant<propertyset_t, fstrenum_t>;
using fdepl_define_t = tuple<fqn_t, fqn_t, vector<data_t>>;
x3::rule<class fdepl_define_id, fdepl_define_t> const fdepl_define { "fdepl_define" };

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
