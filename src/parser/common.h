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

x3::rule<class identifier_id, std::string> const identifier { "identifier" };
x3::rule<class fqn_id, ast::FQN> const fqn { "fqn" };


static struct known_type_parser : x3::symbols<std::string>
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

auto const identifier_def = x3::raw[x3::lexeme[(x3::alpha | '_') >> *(x3::alnum | '_')]];
auto const fqn_def = x3::lexeme[identifier % "."];
auto const whitespace
   = x3::blank
   | x3::lexeme[ "//" >> *(x3::char_ - x3::eol) >> x3::eol ]
   | x3::eol;

BOOST_SPIRIT_DEFINE(identifier, fqn)
}
#endif // COMMON_H
