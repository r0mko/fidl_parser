#pragma once

#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
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

using propvalue_t = x3::variant<bool, int, double, identifier_t>;
x3::rule<class propvalue_id, propvalue_t> const propvalue { "propvalue" };
using property_t = pair<identifier_t, propvalue_t>;
x3::rule<class property_id, property_t> const property { "property" };
using propertyset_t = vector<property_t>;
x3::rule<class propertyset_id, propertyset_t> const propertyset { "propertyset" };

using fmember_t = pair<identifier_t, propertyset_t>;
x3::rule<class fmember_id, fmember_t> const fmember { "fmember" };

using fenum_t = pair<identifier_t, vector<fmember_t>>;
x3::rule<class fenum_id, fenum_t> const fenum { "fenum" };

using fstruct_mem_t = x3::variant<propertyset_t, fmember_t>;
x3::rule<class fstruct_mem_id, fstruct_mem_t> const fstruct_mem { "fstruct_mem" };
using fstruct_t = pair<identifier_t, vector<fstruct_mem_t>>;
x3::rule<class fstruct_id, fstruct_t> const fstruct { "fstruct" };

using fqn_t = vector<identifier_t>;
x3::rule<class fqn_id, fqn_t> const fqn { "fqn" };

x3::rule<class import_id, identifier_t> const import { "import" };

using data_t = x3::variant<propertyset_t, fenum_t, fstruct_t>;
x3::rule<class data_id, data_t> const data { "data" };
using dataset_t = vector<data_t>;
x3::rule<class dataset_id, dataset_t> const dataset { "dataset" };

using fdepl_define_header_t = pair<fqn_t, fqn_t>;
x3::rule<class fdepl_define_header_id, fdepl_define_header_t> const fdepl_define_header { "fdepl_define_header" };
using fdepl_define_t = pair<fdepl_define_header_t, boost::optional<dataset_t>>;
x3::rule<class fdepl_define_id, fdepl_define_t> const fdepl_define { "fdepl_define" };

using fdepl_full_t = pair<identifier_t, boost::optional<fdepl_define_t>>;
x3::rule<class fdepl_full_id, fdepl_full_t> const fdepl_full { "fdepl_full" };

auto const whitespace
   = x3::blank
   | x3::lexeme[ "//" >> *(x3::char_ - x3::eol) >> x3::eol ]
   | x3::eol;

template<typename T>
void introspect(T &ctx) {
   cout << "attr type: " << getTypeName(_attr(ctx)) << endl;
   cout << "val type: " << getTypeName(_val(ctx)) << endl;
};

auto const identifier_def = x3::raw[lexeme[(x3::alpha | '_') >> *(x3::alnum | '_')]];
auto const propvalue_def = bool_ | int_ | double_ | identifier;
auto const property_def = identifier >> lit("=") >> propvalue;
auto const propertyset_def = +(-lit(",") >> property);
auto const fmember_def = identifier >> lit("{") >> propertyset >> lit("}");
auto const fenum_def = lit("enumeration") >> identifier >> '{' >> *(fmember) >> '}';
auto const fstruct_mem_def = propertyset | fmember;
auto const fstruct_def = lit("struct") >> identifier >> '{' >> *(fstruct_mem) >> '}';
auto const fqn_def = identifier % ".";
auto const import_def = lit("import") >> lexeme['"' >> identifier >> lit(".fidl") >> '"'];
auto const data_def = propertyset | fenum | fstruct;
auto const dataset_def = +(data);
auto const fdepl_define_header_def = lit("define") >> fqn >> lit("for") >> lit("typeCollection") >> fqn;
auto const fdepl_define_def =  fdepl_define_header > lit("{") > -dataset > lit("}");
auto const fdepl_full_def = import >> -fdepl_define;

BOOST_SPIRIT_DEFINE(
   identifier,
   propvalue,
   property,
   propertyset,
   fmember,
   fenum,
   fstruct_mem,
   fstruct,
   fqn,
   import,
   data,
   dataset,
   fdepl_define_header,
   fdepl_define,
   fdepl_full);

}
