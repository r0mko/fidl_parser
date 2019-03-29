#ifndef AST_COMMON_H
#define AST_COMMON_H

#include <string>
#include <vector>
#include <boost/algorithm/string/join.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace ast {

using namespace std;

struct FQN
{
    vector<string> path;
    string toString() const
    {
       return boost::algorithm::join(path, ".");
    }
};

}

BOOST_FUSION_ADAPT_STRUCT(
   ast::FQN,
   path);

#endif // COMMON_H
