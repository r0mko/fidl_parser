#ifndef AST_COMMON_H
#define AST_COMMON_H

#include <string>
#include <vector>

namespace ast {

using namespace std;

struct FQN
{
    vector<string> path;
    string toString() const;
};

}

#endif // COMMON_H
