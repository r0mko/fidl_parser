#include "parser.h"
#include <fstream>
#include <sstream>

fidl::known_type_parser::known_type_parser() {
    add("Float", "Float");
    add("Double", "Double");
    add("UInt64", "UInt64");
    add("UInt32", "UInt32");
    add("UInt16", "UInt16");
    add("UInt8", "UInt8");
    add("Int64", "Int64");
    add("Int32", "Int32");
    add("Int16", "Int16");
    add("Int8", "Int8");
    add("Boolean", "Boolean");
    add("String", "String");
}

std::string FrancaParser::readFile(const std::string &filename, bool &ok)
{
    std::ifstream stream(filename);
    ok = stream.good();
    if (!ok) {
        return std::string();
    }
    std::stringstream ss;
    ss << stream.rdbuf();
    return ss.str();
}
