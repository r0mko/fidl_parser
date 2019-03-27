#ifndef AST_H
#define AST_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/optional/optional.hpp>
#include <boost/config/warning_disable.hpp>

namespace ast {
using namespace std;
namespace x3 = boost::spirit::x3;
using boost::optional;

enum DefinitionType {
    Struct,
    TypeDef,
    Enum,
    Invalid
};

struct FStructMember
{
    string type;
    optional<bool> isArray;
    string name;
};

using FAnnotation = std::pair<string, string>;
using FAnnotationBlock = std::vector<FAnnotation>;

struct FTypeBase
{
    optional<FAnnotationBlock> annotation;
    string name;
};

struct FStruct : FTypeBase
{
    optional<string> polymorphic;
    vector<FStructMember> members;
};

struct FTypeDef : FTypeBase
{
    string type;
};

using FEnum_Member = std::pair<string, boost::optional<int>>;

struct FEnum : FTypeBase
{
    vector<FEnum_Member> members;
};

struct FType : x3::variant<FStruct, FTypeDef, FEnum>
{
private:
    struct get_type : public boost::static_visitor<DefinitionType>
    {
        DefinitionType operator()(FStruct) const { return Struct; }
        DefinitionType operator()(FTypeDef) const { return TypeDef; }
        DefinitionType operator()(FEnum) const { return Enum; }
    };

    struct get_name : public boost::static_visitor<string>
    {
        string operator()(FStruct f) const { return f.name; }
        string operator()(FEnum f) const { return f.name; }
        string operator()(FTypeDef f) const { return f.name; }
    };

    struct get_annotation : public boost::static_visitor<optional<FAnnotationBlock>>
    {
        optional<FAnnotationBlock> operator()(const FTypeBase &f) const { return f.annotation; }
    };

public:
    using base_type::base_type;
    using base_type::operator =;
    DefinitionType getType() const { return boost::apply_visitor(get_type(), *this); }
    string getName() const { return boost::apply_visitor(get_name(), *this); }

    bool hasAnnotations() const { return boost::apply_visitor(get_annotation(), *this).is_initialized(); }
    FAnnotationBlock getAnnotations() const { return boost::apply_visitor(get_annotation(), *this).get(); }

    struct to_string : public boost::static_visitor<string>
    {
        string operator()(FStruct f) const {
            ostringstream out;
            out << "struct " << f.name;
            if (f.polymorphic) {
                string base_type = f.polymorphic.get();
                if (!base_type.empty()) {
                    out << " : " << base_type << base_type.size();
                }
            } else {
                out << " final";
            }
            out << endl;
            for (FStructMember mem : f.members) {
                if (mem.isArray) {
                    out << "    vector<" << mem.type << "> " << mem.name;
                } else {
                    out << "    " << mem.type << " " << mem.name;
                }
                out << endl;
            }
            return out.str();
        }

        string operator()(FEnum e) const {
            ostringstream out;
            out << "enum " << e.name << endl;
            for (FEnum_Member mem : e.members) {
                out << "    " << mem.first;
                if (mem.second) {
                    out << " = " << mem.second.get();
                }
                out << endl;
            }
            return out.str();
        }

        string operator()(FTypeDef t) const {
            ostringstream out;


            out << "typedef " << t.name << " -> " << t.type;
            return out.str();
        }
    };
};

ostream & operator << (ostream &out, FType t)
{
    out << boost::apply_visitor(FType::to_string(), t);
    if (t.hasAnnotations()) {
        out << "\nannotations for " << t.getName() << ":" << endl;
        for (auto e : t.getAnnotations()) {
            out << e.first << ": " << e.second << endl;
        }
    }
    return out;
}

struct FVersion
{
    FVersion() {
        std::cout << "Constructed struct version!";
    }
    int major = 0;
    int minor = 0;
};

struct FTypeCollection
{
    string name;
    optional<FVersion> version;
    vector<FType> types;
};
}

BOOST_FUSION_ADAPT_STRUCT(
        ast::FVersion,
        major, minor
        );

BOOST_FUSION_ADAPT_STRUCT(
        ast::FStructMember,
        type, isArray, name
        );
BOOST_FUSION_ADAPT_STRUCT(
    ast::FStruct,
    annotation, name, polymorphic, members
);

BOOST_FUSION_ADAPT_STRUCT(
    ast::FTypeDef,
    annotation, name, type
);

BOOST_FUSION_ADAPT_STRUCT(
    ast::FEnum,
    annotation, name, members
);

BOOST_FUSION_ADAPT_STRUCT(
        ast::FTypeCollection,
        name, version, types
        );


#endif // AST_H
