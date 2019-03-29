#pragma once

#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
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

x3::rule<class identifier_id, ast::fdepl::identifier_t> const identifier { "identifier" };
x3::rule<class propvalue_id, ast::fdepl::propvalue_t> const propvalue { "propvalue" };
x3::rule<class property_id, ast::fdepl::property_t> const property { "property" };
x3::rule<class propertyset_id, ast::fdepl::propertyset_t> const propertyset { "propertyset" };
x3::rule<class fmember_id, ast::fdepl::fmember_t> const fmember { "fmember" };
x3::rule<class fenum_id, ast::fdepl::fenum_t> const fenum { "fenum" };
x3::rule<class fstruct_mem_id, ast::fdepl::fstruct_mem_t> const fstruct_mem { "fstruct_mem" };
x3::rule<class fstruct_id, ast::fdepl::fstruct_t> const fstruct { "fstruct" };
x3::rule<class fqn_id, ast::fdepl::fqn_t> const fqn { "fqn" };
x3::rule<class import_id, ast::fdepl::identifier_t> const import { "import" };
x3::rule<class data_id, ast::fdepl::data_t> const data { "data" };
x3::rule<class dataset_id, ast::fdepl::dataset_t> const dataset { "dataset" };
x3::rule<class fdepl_define_header_id, ast::fdepl::fdepl_define_header_t> const fdepl_define_header { "fdepl_define_header" };
x3::rule<class fdepl_define_id, ast::fdepl::fdepl_define_t> const fdepl_define { "fdepl_define" };
x3::rule<class fdepl_full_id, ast::fdepl::fdepl_full_t> const fdepl_full { "fdepl_full" };

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

struct error_handler
{
   template <typename Iterator, typename Exception, typename Context>
   x3::error_handler_result on_error(
      Iterator& first, Iterator const& last
      , Exception const& x, Context const& context)
   {
      auto& error_handler = x3::get<x3::error_handler_tag>(context).get();
      std::string message = "Error! Expecting: " + x.which() + " here:";
      error_handler(x.where(), message);
      return x3::error_handler_result::fail;
   }
};

class property_id : error_handler, x3::annotate_on_success {};
class fmember_id : error_handler, x3::annotate_on_success {};
class fenum_id : error_handler, x3::annotate_on_success {};
class fstruct_id : error_handler, x3::annotate_on_success {};
class fdepl_define_id : error_handler, x3::annotate_on_success {};
class fdepl_full_id : error_handler, x3::annotate_on_success {};


}
