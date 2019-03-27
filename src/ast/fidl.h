#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/optional/optional.hpp>
#include <boost/algorithm/string/join.hpp>

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
    DefinitionType getType() const;
    string getName() const;

    bool hasAnnotations() const;
    FAnnotationBlock getAnnotations() const;

    struct to_string : public boost::static_visitor<string>
    {
        string operator()(FStruct f) const;
        string operator()(FEnum e) const;
        string operator()(FTypeDef t) const;
    };
};

ostream & operator << (ostream &out, FType t);

struct FVersion
{
    int major = 0;
    int minor = 0;
};

struct FTypeCollection
{
    string name;
    optional<FVersion> version;
    vector<FType> types;
    bool hasType(const string &name) const;
    DefinitionType getTypeByName(const string &name) const;
};

struct FModel
{
    vector<string> packageName;
    // TODO: imports
    vector<FTypeCollection> typeCollections;
    std::string getPackageName() const;
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

BOOST_FUSION_ADAPT_STRUCT(
        ast::FModel,
        packageName, typeCollections
        );
