#include "ast.h"
#include <boost/algorithm/string/join.hpp>

bool ast::FTypeCollection::hasType(const std::string &name) const {
    auto it = std::find_if(types.cbegin(), types.cend(), [&](const FType &t) { return t.getName() == name; });
    return it != types.cend();
}

ast::DefinitionType ast::FTypeCollection::getTypeByName(const std::string &name) const {
    auto it = std::find_if(types.cbegin(), types.cend(), [&](const FType &t) { return t.getName() == name; });
    if (it == types.cend()) {
        return Invalid;
    }
    return (*it).getType();
}

std::ostream &ast::operator <<(std::ostream &out, ast::FType t)
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

std::string ast::FType::to_string::operator()(ast::FStruct f) const {
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

std::string ast::FType::to_string::operator()(ast::FEnum e) const {
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

std::string ast::FType::to_string::operator()(ast::FTypeDef t) const {
    ostringstream out;
    out << "typedef " << t.name << " -> " << t.type;
    return out.str();
}

ast::DefinitionType ast::FType::getType() const
{
    return boost::apply_visitor(get_type(), *this);
}

std::string ast::FType::getName() const
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

std::string ast::FModel::getPackageName() const
{
    return boost::algorithm::join(packageName, ".");
}
