#ifndef PARSER_H
#define PARSER_H

#include "fidl.h"
#include "fdepl.h"

class FrancaParser
{
public:
    static bool parse(const std::string &filename, ast::FModel& fmodel_ast);

private:
    static bool parseFdepl(const std::string &filename, ast::FDModel& fdmodel_ast);
    static bool parseFidl (const std::string &filename, ast::FModel&  fmodel_ast);
    static bool mergeFdeplAndFidl(const ast::FDModel& fdmodel_ast, ast::FModel& fmodel_ast);
    static bool readFile  (const std::string &filename, std::string& out);
};

#endif // PARSER_H
