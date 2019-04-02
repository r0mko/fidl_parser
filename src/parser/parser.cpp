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

franca::keywords_t::keywords_t() {
   add("struct", "struct");
   add("enumeration", "enumeration");
   add("polymorphic", "polymorphic");
   add("extends", "extends");
   add("typedef", "typedef");
   add("version", "version");
   add("typeCollection", "typeCollection");
   add("import", "import");
   add("define", "define");
}

namespace {

bool readFile(const std::string &filename, std::string& out)
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

template<class PARSER, class AST>
bool parseT(const std::string& filename,
            const PARSER& parser,
            AST& model_ast)
{
   std::string fdepl;
   bool result = readFile(filename, fdepl);
   
   typedef std::string::const_iterator iterator_type;
   
   iterator_type iter = fdepl.begin();
   iterator_type const end = fdepl.end();
   
   using boost::spirit::x3::with;
   using boost::spirit::x3::error_handler_tag;
   using error_handler_type = boost::spirit::x3::error_handler<iterator_type>;
   
   error_handler_type error_handler(iter, end, std::cout);
   
   auto const error_capable_parser = with<error_handler_tag>(std::ref(error_handler)) [ parser ];
   
   if (true == result)
   {
      result = x3::phrase_parse(iter, end, error_capable_parser, franca::whitespace, model_ast);
   }
   
   return result && iter == end;
}

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
      result = parseT(fdepl_path.string(), franca::fdmodel, fdmodel_ast);
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
      result = parseT(fidl_path.string(), franca::fmodel, fmodel_ast);
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

