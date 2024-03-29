#pragma once

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/optional/optional.hpp>

#include "ast/common.h"

namespace ast {
using namespace std;
namespace x3 = boost::spirit::x3;
using boost::optional;


enum class FDValueType
{
    Bool,
    Integer,
    Double,
    String
};


struct FDValue : x3::variant<bool, int, double, string>
{
    FDValue() = default;
    FDValue(const FDValue&) = default;
    FDValue& operator= (const FDValue&) = default;

    using base_type::base_type;
    using base_type::operator=;

    ast::FDValueType getType() const;
    bool isBool() const;
    bool isInteger() const;
    bool isDouble() const;
    bool isString() const;

private:
   struct get_type : public boost::static_visitor<ast::FDValueType>
   {
      ast::FDValueType operator()(bool) const { return ast::FDValueType::Bool; }
      ast::FDValueType operator()(int) const { return ast::FDValueType::Integer; }
      ast::FDValueType operator()(double) const { return ast::FDValueType::Double; }
      ast::FDValueType operator()(std::string) const { return ast::FDValueType::String; }
   };
};

struct FDProperty
{
    string name;
    FDValue value;
};

using FDPropertySet = vector<FDProperty>;

struct FDField
{
    string name;
    vector<FDProperty> properties;
};

struct FDTypebase
{
    string name;
    FDPropertySet properties;
};

struct FDTypedef : FDTypebase
{
};

struct FDEnumeration : FDTypebase
{
    vector<FDField> fields;
};

struct FDStruct : FDTypebase
{
    vector<FDField> fields;
};

struct FDTypeDefinition : x3::variant<ast::FDEnumeration, ast::FDStruct, ast::FDTypedef>
{
private:
   struct get_type : public boost::static_visitor<ast::DefinitionType>
   {
      ast::DefinitionType operator()(ast::FDStruct) const { return ast::DefinitionType::Struct; }
      ast::DefinitionType operator()(ast::FDTypedef) const { return ast::DefinitionType::TypeDef; }
      ast::DefinitionType operator()(ast::FDEnumeration) const { return ast::DefinitionType::Enum; }
   };
   
   struct get_name : public boost::static_visitor<string>
   {
       string operator()(const FDEnumeration &f) const { return f.name; }
       string operator()(const FDStruct &f) const { return f.name; }
       string operator()(const FDTypedef &f) const { return f.name; }
   };

public:
   FDTypeDefinition() = default;
   FDTypeDefinition(const FDTypeDefinition&) = default;
   FDTypeDefinition& operator= (const FDTypeDefinition&) = default;

   using base_type::base_type;
   using base_type::operator=;

   string getName() const;
   ast::DefinitionType getType() const;
   bool isStruct() const;
   bool isEnum() const;
   bool isTypedef() const;
};

struct FDTypes
{
    FQN name;
    FQN typeCollectionName;
    FDPropertySet properties;
    vector<FDTypeDefinition> types;
};

struct FDModel
{
    FQN packageName;
    vector<string> imports;
    vector<FDTypes> deployments;    
};



} // namespace ast

BOOST_FUSION_ADAPT_STRUCT(
        ast::FDProperty,
        name, value
        );
BOOST_FUSION_ADAPT_STRUCT(
        ast::FDField,
        name, properties
        );
BOOST_FUSION_ADAPT_STRUCT(
        ast::FDTypedef,
        name, properties
        );
BOOST_FUSION_ADAPT_STRUCT(
        ast::FDStruct,
        name, properties, fields
        );
BOOST_FUSION_ADAPT_STRUCT(
        ast::FDEnumeration,
        name, properties, fields
        );
BOOST_FUSION_ADAPT_STRUCT(
        ast::FDTypes,
        name, typeCollectionName, properties, types
        );

BOOST_FUSION_ADAPT_STRUCT(
        ast::FDModel,
        packageName, imports, deployments
        );

