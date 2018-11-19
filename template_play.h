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

template<typename T>
struct isPtr{
    static const bool value = false; 
};

template<typename T>
struct isPtr<T* >{
    static const bool value = true; 
};

template<typename T>
struct isPtr<T* const>{
    static const bool value = true; 
};

template<typename T>
struct isConst{
    static const bool value = false; 
};

template<typename T>
struct isConst<T const>{
    static const bool value = true; 
};

template<template<typename> typename f1, template<typename> typename f2>
struct orCombinator{
    template<typename T>
    struct lambda{
        static const bool value = f1<T>::value || f2<T>::value;
    };
    
};
#endif /*TEMPLATE_PLAY_H*/