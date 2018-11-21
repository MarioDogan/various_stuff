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

template<template<typename> class predicate, class... list> 
struct all_same_pred;

template<template<typename> class predicate>
struct all_same_pred<predicate>{
    static const bool value = true;
};

template<template<typename> class predicate, typename head, typename... tail>
struct all_same_pred<predicate, head, tail...>{
  static const bool value = predicate<head>::value && all_same_pred<predicate, tail...>::value;
};

struct f_square{
    static constexpr int fun(int val){return val * val;};
};

struct f_sum{
    static constexpr int fun(int val){return ++val;};
};

template<typename T, int val>
struct foldR{
  static constexpr int value = T::fun(val);  
};

template<template<typename, int> class, int, typename...>
struct fold_right;

template<template<typename,int> class f, int init>
struct fold_right<f, init>{
    static constexpr int value = init;
};

template<template<typename,int> typename f, int init, typename head, typename... tail>
struct fold_right<f,init,head,tail...>{
    static constexpr int value = f<head,fold_right<f,init,tail... >::value>::value;
};

template<int...> 
struct sum_;

template<>
struct sum_<>{
    static constexpr int value = 0;
};

template<int head, int... tail>
struct sum_<head, tail...>{
    static constexpr int value = head + sum_<tail...>::value;
};

#endif /*TEMPLATE_PLAY_H*/