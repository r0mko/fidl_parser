#ifndef AST_COMMON_H
#define AST_COMMON_H

#include <string>
#include <vector>
#include <boost/algorithm/string/join.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace ast {

using namespace std;

struct FQN : public vector<string>
{
    string toString() const;
};

}

#endif // COMMON_H
