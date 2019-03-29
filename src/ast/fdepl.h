#pragma once

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/optional/optional.hpp>

namespace ast {
namespace fdepl {

using namespace std;
namespace x3 = boost::spirit::x3;
using boost::optional;

using identifier_t = string;
using propvalue_t = x3::variant<bool, int, double, identifier_t>;

struct property_t : x3::position_tagged
{
    identifier_t name;
    propvalue_t  value;
};

using propertyset_t = vector<property_t>;

struct fmember_t : x3::position_tagged
{
    identifier_t    name;
    propertyset_t   properties;
};

struct fenum_t : x3::position_tagged
{
    identifier_t        name;
    vector<fmember_t>   members;
};

using fstruct_mem_t = x3::variant<propertyset_t, fmember_t>;
struct fstruct_t : x3::position_tagged
{
    identifier_t            name;
    vector<fstruct_mem_t>   members;
};
using fqn_t = vector<identifier_t>;
using data_t = x3::variant<propertyset_t, fenum_t, fstruct_t>;
using fdepl_define_header_t = pair<fqn_t, fqn_t>;
struct fdepl_define_t : x3::position_tagged
{
    fdepl_define_header_t  header;
    vector<data_t>         data;
};

struct fdepl_full_t : x3::position_tagged
{
   vector<identifier_t>    imports;
   vector<fdepl_define_t>  defines;
};

using boost::fusion::operator<<;
}
} // namespace ast

BOOST_FUSION_ADAPT_STRUCT(ast::fdepl::property_t, name, value);
BOOST_FUSION_ADAPT_STRUCT(ast::fdepl::fmember_t, name, properties);
BOOST_FUSION_ADAPT_STRUCT(ast::fdepl::fenum_t, name, members);
BOOST_FUSION_ADAPT_STRUCT(ast::fdepl::fstruct_t, name, members);
BOOST_FUSION_ADAPT_STRUCT(ast::fdepl::fdepl_define_t, header, data);
BOOST_FUSION_ADAPT_STRUCT(ast::fdepl::fdepl_full_t, imports, defines);
