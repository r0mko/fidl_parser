#include <iostream>
#include <map>

#include "ast/ast.h"
#include "parser/parser.h"
#include "constants.h"

// --- test
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
// --- teset

using namespace std;

franca::known_type_parser franca::known_type = franca::known_type_parser();

namespace ast2 {
namespace x3 = boost::spirit::x3;

struct VarDef : x3::position_tagged
{
    std::string type;
    std::string name;
};

struct StructField : x3::position_tagged
{
    std::string type;
    std::string name;
};

struct StructDef : x3::position_tagged
{
    std::string name;
    std::vector<StructField> fields;
};

struct Typedef : x3::position_tagged
{
    std::string name;
    std::string targetType;
};

struct Definition : x3::variant<Typedef, StructDef>
{
    using base_type::base_type;
    using base_type::operator =;
};
}

BOOST_FUSION_ADAPT_STRUCT(ast2::VarDef, type, name)
BOOST_FUSION_ADAPT_STRUCT(ast2::StructField, type, name)
BOOST_FUSION_ADAPT_STRUCT(ast2::StructDef, name, fields)
BOOST_FUSION_ADAPT_STRUCT(ast2::Typedef, name, targetType)

namespace parser {
namespace x3 = boost::spirit::x3;

struct error_handler
{
    template <typename Iterator, typename Exception, typename Context>
    x3::error_handler_result on_error(Iterator& first, Iterator const& last, Exception const& x, Context const& context)
    {
        auto& error_handler = x3::get<x3::error_handler_tag>(context).get();
        std::cout << "got: \"" << std::string(first, last) << '"' << std::endl;
        std::string message = "Error! Expected " + x.which() + " here:";
        error_handler(x.where(), message);
        return x3::error_handler_result::fail;
    }
};

struct identifier_id;
struct vardef_id;
struct struct_field_id;
struct struct_def_id;
struct typealias_id;
struct model_id;

auto const identifier
   = x3::rule<identifier_id, std::string> { "identifier" }
   = x3::raw[x3::lexeme[(x3::alpha | '_') >> *(x3::alnum | '_')]];

using franca::known_type_parser;
const known_type_parser known_type_p = known_type_parser();
const auto known_type = x3::rule<class known_type_id, std::string> { "known type" } = known_type_p;
const x3::rule<vardef_id, ast2::VarDef> vardef { "var_def" };
const x3::rule<struct_field_id, ast2::StructField> struct_field { "struct_field" };
const x3::rule<struct_def_id, ast2::StructDef> struct_def { "struct" };
const x3::rule<typealias_id, ast2::Typedef> typealias { "struct" };

const auto vardef_def = known_type > identifier;
const auto struct_field_def = known_type > identifier > ";";
const auto struct_fields = x3::rule<class struct_fields_id, std::vector<ast2::StructField>> {"struct_fields"} = *(struct_field);
const auto struct_def_def = "struct" > identifier > "{" > struct_fields > "}" > ";";
const auto typealias_def = "typedef" > identifier > "is" > known_type > ";";
const auto definition = x3::rule<class definition_id, ast2::Definition> {"definition of type"} = typealias | struct_def;
const auto model = x3::rule<model_id, std::vector<ast2::Definition>> {"model"} = +(definition);

BOOST_SPIRIT_DEFINE(vardef, struct_field, struct_def, typealias);

struct identifier_id : x3::annotate_on_success{};
struct struct_def_id : error_handler, x3::annotate_on_success {};
struct struct_field_id : x3::annotate_on_success {};
struct vardef_id : x3::annotate_on_success {};
struct typealias_id : error_handler, x3::annotate_on_success {};
struct model_id : error_handler, x3::annotate_on_success {};

}

const std::string good_input = R"(

struct Foo {
   UInt8 a;
   Double dbl;
   String name;
};

)";
const std::string bad_input = R"(

struct Bar {
    UInt8 a;
    String name;
    Double dbl;
    Boolean boo;
};

typedef Angle is Float;

typedef Name is Foo;


)";

void parse(std::string const& input)
{
    using boost::spirit::x3::ascii::space;
    typedef std::string::const_iterator iterator_type;

    std::vector<ast2::Definition> ast;
    iterator_type iter = input.begin();
    iterator_type const end = input.end();

    using boost::spirit::x3::with;
    using boost::spirit::x3::error_handler_tag;
    using error_handler_type = boost::spirit::x3::error_handler<iterator_type>;

    error_handler_type error_handler(iter, end, std::cout);

    using parser::model;
    auto const parser = with<error_handler_tag>(std::ref(error_handler)) [ model ];

    bool r = phrase_parse(iter, end, parser, franca::whitespace, ast);

    if (r && iter == end)
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded\n";
        std::cout << "-------------------------\n";
    }
    else
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------\n";
    }
}

int main(int argc, const char *argv[])
{

    namespace x3 = boost::spirit::x3;
    using namespace std;

    parse(good_input);
    parse(bad_input);

    return 0;

    if (argc < 2) {
        cerr << "No input file provided!" << endl <<  "Usage: spirit_parser [fidl_file]" << endl;
        exit(1);
    }

    ast::FModel output;
    bool ok = FrancaParser::parse(argv[1], output);

    int i = 0;
    if (true == ok)
    {
        cout << endl << "Successfully parsed fidl package " << output.getPackageName() << ", got " << output.typeCollections.size() << " typecollection";
        if (output.typeCollections.size() > 1) {
            cout << "s";
        }
        cout << endl;
        for (const ast::FTypeCollection &tc : output.typeCollections) {
            cout << "TypeCollection " << tc.name;
            if (!tc.version) {
                cout << " without version specifier";
            } else {
                ast::FVersion ver = tc.version.get();
                cout << " version " << ver.major << "." << ver.minor;
            }
            cout << endl << endl << "Element count: " << tc.types.size() << endl;

            for(const auto &element : tc.types) {
                cout << "Element " << ++i << ": " << element;
                cout << endl;
            }
        }
    }
    cout << endl << "Known types: ";
    franca::known_type.for_each([](string s, string ) { std::cout << s << " "; });
    std::cout<<std::endl;

    return 0;
}
