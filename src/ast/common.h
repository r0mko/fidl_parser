#pragma once

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
