#include "ast.h"
#include <boost/algorithm/string/join.hpp>

using namespace std;
using boost::optional;

bool ast::FTypeCollection::hasType(const string &name) const {
    auto it = find_if(types.cbegin(), types.cend(), [&](const FType &t) { return t.getName() == name; });
    return it != types.cend();
}

ast::DefinitionType ast::FTypeCollection::getTypeByName(const string &name) const {
    auto it = find_if(types.cbegin(), types.cend(), [&](const FType &t) { return t.getName() == name; });
    if (it == types.cend()) {
        return DefinitionType::Invalid;
    }
    return (*it).getType();
}

ostream &ast::operator <<(ostream &out, ast::FType t)
{
    out << boost::apply_visitor(FType::to_string(), t);
    if (t.hasAnnotations()) {
        out << "\nannotations for " << t.getName() << ":" << endl;
        for (const auto &e : t.getAnnotations()) {
            out << e.first << ": " << e.second << endl;
        }
    }
    return out;
}

string ast::FType::to_string::operator()(ast::FStruct f) const {
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
    out << "Tag is " << f.tag << endl;
    for (const FStructMember &mem : f.members) {
        if (mem.isArray) {
            out << "    vector<" << mem.type << "> " << mem.name;
        } else {
            out << "    " << mem.type << " " << mem.name;
        }
        out << endl;
    }
    return out.str();
}

string ast::FType::to_string::operator()(ast::FEnum e) const {
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

string ast::FType::to_string::operator()(ast::FTypeDef t) const {
    ostringstream out;
    out << "typedef " << t.name << " -> " << t.type;
    return out.str();
}

ast::DefinitionType ast::FType::getType() const
{
    return boost::apply_visitor(get_type(), *this);
}

string ast::FType::getName() const
{
    return boost::apply_visitor(get_name(), *this);
}

bool ast::FType::hasAnnotations() const
{
    return boost::apply_visitor(get_annotation(), *this).is_initialized();
}

ast::FAnnotationBlock ast::FType::getAnnotations() const
{
    return boost::apply_visitor(get_annotation(), *this).get();
}

pair<ast::FModel::TCConstIterator, ast::FModel::FTypeConstIterator> ast::FModel::findTypeByName(const string &name) const
{
    auto i_tc = typeCollections.cbegin();
    while (i_tc != typeCollections.cend()) {
        const FTypeCollection &tc = *i_tc;
        auto i_t = find_if(tc.types.cbegin(), tc.types.cend(), [&](const FType &t) { return t.getName() == name; });
        if (i_t != tc.types.cend()) {
            return { i_tc, i_t };
        }
        ++i_tc;
    }
    return { i_tc, typeCollections.back().types.cend() };
}

pair<ast::FModel::TCIterator, ast::FModel::FTypeIterator> ast::FModel::findTypeByName(const string &name)
{
    auto i_tc = typeCollections.begin();
    while (i_tc != typeCollections.end()) {
        FTypeCollection &tc = *i_tc;
        auto i_t = find_if(tc.types.begin(), tc.types.end(), [&](const FType &t) { return t.getName() == name; });
        if (i_t != tc.types.end()) {
            return { i_tc, i_t };
        }
        ++i_tc;
    }
    return { i_tc, typeCollections.back().types.end() };
}

optional<ast::FType> ast::FModel::getTypeByName(const string &name) const
{
    auto ipair = findTypeByName(name);
    if (ipair.first != typeCollections.cend()) {
        return  *(ipair.second);
    }
    return boost::none;
}

string ast::FModel::getPackageName() const
{
   return packageName.toString();
}

string ast::FQN::toString() const
{
    return boost::algorithm::join(*this, ".");
}

string ast::FDTypeDefinition::getName() const
{
    return boost::apply_visitor(get_name(), *this);
}

ast::DefinitionType ast::FDTypeDefinition::getType() const
{
    return boost::apply_visitor(get_type(), *this);
}

bool ast::FDTypeDefinition::isStruct() const
{
    return getType() == ast::DefinitionType::Struct;
}

bool ast::FDTypeDefinition::isEnum() const
{
    return getType() == ast::DefinitionType::Enum;
}

bool ast::FDTypeDefinition::isTypedef() const
{
    return getType() == ast::DefinitionType::TypeDef;
}

ast::FDValueType ast::FDValue::getType() const
{
    return boost::apply_visitor(get_type(), *this);
}

bool ast::FDValue::isBool() const
{
    return getType() == ast::FDValueType::Bool;
}

bool ast::FDValue::isInteger() const
{
    return getType() == ast::FDValueType::Integer;
}

bool ast::FDValue::isDouble() const
{
    return getType() == ast::FDValueType::Double;
}

bool ast::FDValue::isString() const
{
    return getType() == ast::FDValueType::String;
}
