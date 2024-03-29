#ifndef AST_COMMON_H
#define AST_COMMON_H

#include <string>
#include <vector>
#include <boost/algorithm/string/join.hpp>

namespace ast {

using namespace std;

enum class DefinitionType {
   Struct,
   TypeDef,
   Enum,
   Invalid
};

struct FQN : public vector<string>
{
    string toString() const;
};

}

#endif // COMMON_H
