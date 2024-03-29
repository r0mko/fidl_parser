#include "parser.h"
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/variant.hpp>
#include "ast/common.h"

namespace x3 = boost::spirit::x3;

franca::known_type_parser::known_type_parser() {
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


bool FrancaParser::parse(const std::string& filename, ast::FModel& fmodel_ast)
{
   boost::filesystem::path fdepl_path(filename);
   bool result = false;
   
   do
   {
      result = boost::filesystem::exists(fdepl_path);
      if (false == result)
      {
         std::cerr<<"File "<<fdepl_path.string()<<" does not exist"<<std::endl;
         break;
      }
      
      boost::filesystem::path dir = fdepl_path.parent_path();
      
      ast::FDModel fdmodel_ast;
      result = parseFdepl(fdepl_path.string(), fdmodel_ast);
      if (false == result)
      {
         std::cerr<<"Error parsing FDepl "<<fdepl_path.string()<<std::endl;
         break;
      }
      
      result = (false == fdmodel_ast.imports.empty());
      if (false == result)
      {
         std::cerr<<"No imports in FDepl "<<fdepl_path.string()<<std::endl;
         break;
      }
      
      boost::filesystem::path fidl_path = dir / (fdmodel_ast.imports.at(0) + ".fidl");
      result = parseFidl(fidl_path.string(), fmodel_ast);
      if (false == result)
      {
         std::cerr<<"Error parsing Fidl "<<fidl_path.string()<<std::endl;
         break;
      }
      
      result = mergeFdeplAndFidl(fdmodel_ast, fmodel_ast);
      if (false == result)
      {
         std::cerr<<"Error merging FDepl "<<fdepl_path.string()<< " and Fidl " << fidl_path.string() <<std::endl;
         break;
      }
      
   }
   while (false);
   
   return result;
}

bool FrancaParser::parseFdepl(const std::string& filename, ast::FDModel& fdmodel_ast)
{
   std::string fdepl;
   bool result = readFile(filename, fdepl);
   
   if (true == result)
   {
      result = x3::phrase_parse(fdepl.begin(), fdepl.end(), franca::fdmodel, franca::whitespace, fdmodel_ast);
   }
   
   return result;
}

bool FrancaParser::parseFidl(const std::string& filename, ast::FModel& fmodel_ast)
{
   std::string fidl;
   bool result = readFile(filename, fidl);
   
   if (true == result)
   {
      result = x3::phrase_parse(fidl.begin(), fidl.end(), franca::fmodel, franca::whitespace, fmodel_ast);
   }
   
   return result;
}

bool FrancaParser::mergeFdeplAndFidl(const ast::FDModel& fdmodel_ast, ast::FModel& fmodel_ast)
{
   bool result = true;
   
   for (const auto& deployment : fdmodel_ast.deployments)
   {
      for (const auto& fdtype : deployment.types)
      {
         if (ast::DefinitionType::Struct == fdtype.getType())
         {
            const auto typeName = fdtype.getName();
            auto iterPair = fmodel_ast.findTypeByName(typeName);
            if (iterPair.first != fmodel_ast.typeCollections.end() &&
                iterPair.second != iterPair.first->types.end())
            {
                const auto& fdstruct = boost::get<ast::FDStruct>(fdtype);
                const auto it = std::find_if(fdstruct.properties.begin(),
                                             fdstruct.properties.end(),
                                             [](const ast::FDProperty& prop)
                {
                    return prop.name == "Tag";
                });
                if (it != fdstruct.properties.end() &&
                    it->value.isInteger())
                {
                    const auto value = boost::get<int>(it->value);
                    ast::FStruct& fstruct = boost::get<ast::FStruct>(*iterPair.second);
                    fstruct.tag = value;
                }
            }
         }
      }
   }
   return result;
}

bool FrancaParser::readFile(const std::string &filename, std::string& out)
{
    std::ifstream stream(filename);
    if (!stream.good())
    {
        return false;
    }
    std::stringstream ss;
    ss << stream.rdbuf();
    out = ss.str();
    return true;
}
