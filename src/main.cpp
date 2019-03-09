#include <iostream>
#include <map>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <cxxabi.h>

using namespace std;

string input = "typedef Timestamp is UInt64 \n"
               "struct Vector {             \n"
               "    Float x                 \n"
               "    Float y                 \n"
               "    Float z                 \n"
               "}                           \n"
               "struct Foo {                \n"
               "    Timestamp date          \n"
               "    Vector direction        \n"
               "}\n";

namespace x3 = boost::spirit::x3;
namespace ascii = boost::spirit::x3::ascii;

using String = std::string;

using x3::int_;
using x3::lit;
using x3::double_;
using x3::lexeme;
using ascii::char_;
using x3::_val;
using x3::_attr;

class FStruct_member_class;
class FStruct_class;
class FTypeDef_class;
class identifier_class;
class type_name_class;

template <typename T>
String getTypeName(const T &v) {
    int status;
    char *realname = abi::__cxa_demangle(typeid(decltype(v)).name(), nullptr, nullptr, &status);
    String ret(realname);
    free(realname);
    return ret;
}

namespace ast {

enum DefinitionType {
    Struct,
    TypeDef,
    Enum,
    Invalid
};

struct FStruct
{
    String name;
    String base;
    std::vector<std::pair<String, String>> members;
};

struct FEnum
{
    String name;
    std::vector<std::pair<String, int>> members;
};

using FTypeDef = std::pair<String, String>;

struct FType : x3::variant<
        FStruct,
        FEnum,
        FTypeDef
        >
{
    using base_type::base_type;
    using base_type::operator =;

    struct get_type : public boost::static_visitor<DefinitionType>
    {
       DefinitionType operator()(FStruct) const { return Struct; }
       DefinitionType operator()(FTypeDef) const { return TypeDef;    }
       DefinitionType operator()(FEnum) const { return Enum; }
    };

    DefinitionType getType() const { return boost::apply_visitor(get_type(), *this); }

};

}


//void func(auto &ctx) {
//    cout << getTypeName(ctx) << endl;
//}

int main()
{
    cout << input << endl;

    auto callback = [&](auto& ctx){
        _val(ctx).second = _attr(ctx);
    };

    auto gettype = [&](auto &ctx) {
        cout << "gettype attr: " << getTypeName(_attr(ctx)) << endl;
        _val(ctx).first = _attr(ctx);
    };

    auto foo = [&](auto &ctx) {
        cout << "foo attr: " << getTypeName(_attr(ctx)) << endl;
        cout << "foo val: " << getTypeName(_val(ctx)) << endl;
        _val(ctx).members.push_back(_attr(ctx));
    };

    auto beginstruct = [&](auto &ctx) {
        std::cout << "Begin struct: " << _attr(ctx) << endl;
        _val(ctx).name = _attr(ctx);
    };

    x3::symbols<uint> known_type;

    auto getstruct = [&](auto &ctx) {
        cout << "getstruct attr: " << getTypeName(_attr(ctx)) << endl;
        known_type.add(_attr(ctx).name, 0);
        for (auto p : _attr(ctx).members) {
            cout << "Type: " << p.first << " name: " << p.second << endl;
        }
    };
    auto gettypedef = [&](auto &ctx) {
        cout << "gettypedef attr: " << getTypeName(_attr(ctx)) << endl;
    };

    auto known_type_to_str = [&](auto &ctx) {
        cout << "known_type_to_str attr: " << getTypeName(_attr(ctx)) << endl;
    };

    auto identifier = x3::rule<class identifier_class, String>{} = x3::lexeme[(x3::alpha | '_') >> *(x3::alnum | '_')];

    auto builtin_type = x3::rule<class builtin_type, String>{} =
        x3::string("Float")
        | x3::string("Double")
        | x3::string("UInt64")
        | x3::string("UInt32")
        | x3::string("UInt16")
        | x3::string("UInt8")
        | x3::string("Int64")
        | x3::string("Int32")
        | x3::string("Int16")
        | x3::string("Int8")
        | x3::string("Boolean");

    auto type_name = x3::rule<type_name_class, String> {} =
        builtin_type | known_type [known_type_to_str];

    auto FStruct_member = x3::rule<class FStruct_member_class, std::pair<String, String>>{}
        = type_name >> identifier [callback];

    auto FStruct = x3::rule<class FStruct_class, ast::FStruct> {}
        = lit("struct") >> identifier[beginstruct] >> "{" >> *FStruct_member[foo] >> "}";

    // typedef Offset is UInt32
    auto FTypeDef = x3::rule<class FTypeDef_class, std::pair<String, String>>{}
        = "typedef" >> identifier >> "is" >> type_name;



    auto FDef = FStruct[getstruct] | FTypeDef[gettypedef];







    auto first = input.begin();
    auto last = input.end();

    bool result = x3::phrase_parse(first, last, FStruct[getstruct], x3::space);
    cout << endl << "Result:" << result << endl;
    cout << endl << "Known types: ";
    known_type.for_each([](String s, uint) { std::cout << s << " "; });


    return 0;
}
