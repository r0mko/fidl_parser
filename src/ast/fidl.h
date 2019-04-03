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

#include "ast/common.h"

namespace ast {
using namespace std;
namespace x3 = boost::spirit::x3;
using boost::optional;

struct FStructMember : x3::position_tagged
{
    string type;
    optional<bool> isArray;
    string name;
};

using FAnnotation = std::pair<string, string>;
using FAnnotationBlock = std::vector<FAnnotation>;

struct FTypeBase : x3::position_tagged
{
    optional<FAnnotationBlock> annotation;
    string name;
};

struct FStruct : FTypeBase
{
    optional<string> polymorphic;
    vector<FStructMember> members;
    boost::optional<int> tag;
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
        DefinitionType operator()(FStruct) const { return DefinitionType::Struct; }
        DefinitionType operator()(FTypeDef) const { return DefinitionType::TypeDef; }
        DefinitionType operator()(FEnum) const { return DefinitionType::Enum; }
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
    FType() = default;
    FType(const FType&) = default;
    FType& operator= (const FType&) = default;

    using base_type::base_type;
    using base_type::operator =;

    DefinitionType getType() const;
    string getName() const;

    bool hasAnnotations() const;
    FAnnotationBlock getAnnotations() const;

    struct to_string : public boost::static_visitor<string>
    {
        string operator()(const FStruct& f) const;
        string operator()(const FEnum& e) const;
        string operator()(const FTypeDef& t) const;
    };
};

ostream & operator << (ostream &out, FType t);

struct FVersion : x3::position_tagged
{
    int major = 0;
    int minor = 0;
};

struct FTypeCollection : x3::position_tagged
{
    string name;
    optional<FVersion> version;
    vector<FType> types;
    bool hasType(const string &name) const;
    DefinitionType getTypeByName(const string &name) const;
};

struct FModel : x3::position_tagged
{
   ast::FQN packageName;
    // TODO: imports
   vector<FTypeCollection> typeCollections;
   using TCConstIterator = decltype (typeCollections)::const_iterator;
   using FTypeConstIterator = decltype (FTypeCollection::types)::const_iterator;
   using TCIterator = decltype (typeCollections)::iterator;
   using FTypeIterator = decltype (FTypeCollection::types)::iterator;
   pair<TCConstIterator, FTypeConstIterator> findTypeByName(const string &name) const;
   pair<TCIterator, FTypeIterator> findTypeByName(const string &name);
   optional<FType> getTypeByName(const string &name) const;
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
