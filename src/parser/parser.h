#pragma once

#include "fidl.h"
#include "fdepl.h"

class FrancaParser
{
public:
    FrancaParser() {}
    static std::string readFile(const std::string &filename, bool &ok);
};
