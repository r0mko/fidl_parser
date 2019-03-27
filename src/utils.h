#pragma once
#include <string>
#ifdef __UNIX__
#include <cxxabi.h>
#endif
template <typename T>
std::string getTypeName(const T &v) {
#ifdef __UNIX__
    int status;
    char *realname = abi::__cxa_demangle(typeid(decltype(v)).name(), nullptr, nullptr, &status);
    std::string ret(realname);
    free(realname);
#else
    const char *realname = typeid(decltype(v)).name();
    std::string ret(realname);
#endif
    return ret;
}
