#pragma once

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/optional/optional.hpp>

#include "ast/common.h"

namespace ast {
using namespace std;
namespace x3 = boost::spirit::x3;

using FDValue = x3::variant<bool, int, double, string>;
//struct FDValue : x3::variant<bool, int, double, string>
//{
//    using base_type::base_type;
//    using base_type::operator=;
//};

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

//using FDTypeDefinition = x3::variant<ast::FDEnumeration, ast::FDStruct, ast::FDTypedef>;
struct FDTypeDefinition : x3::variant<ast::FDEnumeration, ast::FDStruct, ast::FDTypedef>
{
   struct get_type : public boost::static_visitor<FDTypeDefinition>
   {
      ast::DefinitionType operator()(ast::FDStruct) const { return ast::DefinitionType::Struct; }
      ast::DefinitionType operator()(ast::FDTypedef) const { return ast::DefinitionType::TypeDef; }
      ast::DefinitionType operator()(ast::FDEnumeration) const { return ast::DefinitionType::Enum; }
   };
   
   using base_type::base_type;
   using base_type::operator=;
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

