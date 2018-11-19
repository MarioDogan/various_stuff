#ifndef TEMPLATE_PLAY_H
#define TEMPLATE_PLAY_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

template<typename T>
std::string to_string_impl(const T& param)
{
    std::stringstream ss;
    ss << param;
    return ss.str();
}

std::vector<std::string> to_string()
{
    return{};
}

template<typename T, typename... Args>
std::vector<std::string> to_string(const T& first, const Args&... args)
{
    std::vector<std::string> tmp;
    tmp.push_back(to_string_impl(first));
    const auto remain = to_string(args...);
    tmp.insert(tmp.end(),remain.begin(),remain.end());
    return tmp;
}
#endif /*TEMPLATE_PLAY_H*/