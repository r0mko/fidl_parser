#ifndef PARSER_COMMON_H
#define PARSER_COMMON_H

#include <boost/spirit/home/x3.hpp>
#include <string>
#include <iostream>
#include "utils.h"
#include "ast/common.h"

namespace franca {

// FIXME: remove. This is a helper function for debugging purposes.
template<typename T>
void introspect(T &ctx) {
    std::cout << "attr type: " << getTypeName(_attr(ctx)) << std::endl;
    std::cout << "val type: " << getTypeName(_val(ctx)) << std::endl;
};

namespace x3 = boost::spirit::x3;

using x3::int_;
using x3::lit;
using x3::double_;
using x3::lexeme;
using x3::_val;
using x3::bool_;
using x3::_attr;

extern struct known_type_parser : x3::symbols<std::string>
{
    known_type_parser();
} known_type;

auto const add_type = [](auto &ctx)
{
    std::string name =_attr(ctx).getName();
    std::cout << "Added new type " << name << std::endl;
    known_type.add(name, name);
    _val(ctx).push_back(_attr(ctx));
};

auto const identifier
   = x3::rule<class identifier_id, std::string> { "identifier" }
   = x3::raw[x3::lexeme[(x3::alpha | '_') >> *(x3::alnum | '_')]];

auto const fqn
   = x3::rule<class fqn_id, ast::FQN> { "fqn" }
   = x3::lexeme[identifier % "."];
   
auto const package
   = x3::rule<class package_id, ast::FQN> { "package" }
   = lit("package") >> fqn;

auto const whitespace
   = x3::blank
   | x3::lexeme[ "//" >> *(x3::char_ - x3::eol) >> x3::eol ]
   | x3::eol;

}
#endif // COMMON_H
