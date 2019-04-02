#pragma once

#include "common.h"
#include "fidl.h"
#include "fdepl.h"

class FrancaParser
{
public:
    static bool parse(const std::string &filename, ast::FModel& fmodel_ast);
    
private:
    static bool mergeFdeplAndFidl(const ast::FDModel& fdmodel_ast, ast::FModel& fmodel_ast);
};
