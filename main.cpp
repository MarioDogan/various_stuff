#include <stdio.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <chrono>
#include "command.h"
#include "command_vrtp.h"
#include <cstring>
#include "template_play.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "range_stuff.h"

using namespace ranges;

class dummyActor{
public:
    void execute(){count += count * 2;}
    uint64_t count{1};
};

class dummyActor2{
public:
    void execute(){std::cout << "execute dummyActor 2\n";}
};

template <typename... Ts>
struct Overloader : Ts... {
    using Ts::operator()...; // exposes operator() from every base
};
 
template <typename... T>
Overloader(T...) -> Overloader<T...>; // C++17 deduction guide
 
#if 0

#include <kfr/base.hpp>
#include <kfr/dsp.hpp>
#include <kfr/io.hpp>

using namespace kfr;
void kfr_test()
{
    println(library_version());

    const std::string options = "phaseresp=True";

    univector<fbase, 128> output;
    {
        biquad_params<fbase> bq[] = { biquad_notch(0.1, 0.5), biquad_notch(0.2, 0.5), biquad_notch(0.3, 0.5),
                                      biquad_notch(0.4, 0.5) };
        output                    = biquad(bq, unitimpulse());
    }
    plot_save("biquad_notch", output, options + ", title='Four Biquad Notch filters'");

    {
        biquad_params<fbase> bq[] = { biquad_lowpass(0.2, 0.9) };
        output                    = biquad(bq, unitimpulse());
    }
    plot_save("biquad_lowpass", output, options + ", title='Biquad Low pass filter (0.2, 0.9)'");

    {
        biquad_params<fbase> bq[] = { biquad_highpass(0.3, 0.1) };
        output                    = biquad(bq, unitimpulse());
    }
    plot_save("biquad_highpass", output, options + ", title='Biquad High pass filter (0.3, 0.1)'");

    {
        biquad_params<fbase> bq[] = { biquad_peak(0.3, 0.5, +9.0) };
        output                    = biquad(bq, unitimpulse());
    }
    plot_save("biquad_peak", output, options + ", title='Biquad Peak filter (0.2, 0.5, +9)'");

    {
        biquad_params<fbase> bq[] = { biquad_peak(0.3, 3.0, -2.0) };
        output                    = biquad(bq, unitimpulse());
    }
    plot_save("biquad_peak2", output, options + ", title='Biquad Peak filter (0.3, 3, -2)'");

    {
        biquad_params<fbase> bq[] = { biquad_lowshelf(0.3, -1.0) };
        output                    = biquad(bq, unitimpulse());
    }
    plot_save("biquad_lowshelf", output, options + ", title='Biquad low shelf filter (0.3, -1)'");

    {
        biquad_params<fbase> bq[] = { biquad_highshelf(0.3, +9.0) };
        output                    = biquad(bq, unitimpulse());
    }
    plot_save("biquad_highshelf", output, options + ", title='Biquad high shelf filter (0.3, +9)'");

    {
        biquad_params<fbase> bq[] = { biquad_bandpass(0.25, 0.2) };
        output                    = biquad(bq, unitimpulse());
    }
    plot_save("biquad_bandpass", output, options + ", title='Biquad band pass (0.25, 0.2)'");

    {
        // filter initialization
        biquad_params<fbase> bq[]       = { biquad_lowpass(0.2, 0.9) };
        expression_filter<fbase> filter = to_filter(biquad(bq, placeholder<fbase>()));

        // prepare data
        output = unitimpulse();

        // apply filter
        filter.apply(output);
    }
    plot_save("biquad_custom_filter_lowpass", output,
              options + ", title='Biquad Low pass filter (0.2, 0.9) (using expression_filter)'");

    {
        // filter initialization
        biquad_params<fbase> bq[] = { biquad_lowpass(0.2, 0.9) };
        biquad_filter<fbase> filter(bq);

        // prepare data
        output = unitimpulse();

        // apply filter
        filter.apply(output);
    }
    plot_save("biquad_filter_lowpass", output,
              options + ", title='Biquad Low pass filter (0.2, 0.9) (using biquad_filter)'");
}
#endif

int test(const int num1, const int num2, const int num3) {
    std::cout << "num1 " << num1 <<'\n';
    std::cout << "num2 " << num2 <<'\n';
    std::cout << "num3 " << num3 <<'\n';
    return 0;
}

struct dum{
    uint8_t tArr2[4096];
};

uint8_t tArr2[4096] = {0};

namespace my_view
{
    my_ranges::add_constant_fn constexpr add_constant;
}

int main(int argc, char **argv)
{
    auto ptr = std::make_shared<dummyActor>();
    generic_at_cmd_sink cmd1{std::make_unique<dummyActor>()};
    generic_at_cmd_sink cmd2{std::make_unique<dummyActor2>()};
    generic_at_cmd<dummyActor> cmd3;
    generic_at_cmd_2<dummyActor> cmd5;
   // SampleVisitor<dummyActor> visit;
    auto qu = make_variant_queue<dummyActor>();
    auto var = make_variant<dummyActor>();
    cmd3.setActor(ptr);
    cmd5.setActor(ptr);
    var = cmd3;
    //int i = 0;
    auto dum1 = std::make_unique<dum>();
    std::cout << "Sizeof " << sizeof(dum1->tArr2) << '\n';
    //test(i++, i++, i++);
  /*  std::cout << var.index() << '\n';
    qu.push(var);
    var = cmd5;
    std::cout << var.index() << '\n';*/
    const std::chrono::time_point<std::chrono::steady_clock> trigger_Start = std::chrono::steady_clock::now();
    for(int64_t i = 0; i < 1; ++i)
    {
        uint8_t *tArr = (uint8_t *)calloc(1,4096);
       /* qu.push(var);
        auto front_value=std::move(qu.front());
        qu.pop();
        std::visit(visit,front_value);*/
        tArr[0] = 1;
        tArr[2048] = 1;
        free(tArr);
        //execute_cmd(cmd3);
    }
    const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - trigger_Start);
    std::cout << diff.count() << " ms\n";
    //std::cout << ptr->count << '\n';
    
    generic_vrtp<dummyActor> cm_vrtp_2;
    auto cm_vrtp = std::make_shared<generic_vrtp<dummyActor>>();
    cm_vrtp->setActor(ptr);
    cm_vrtp_2.setActor(ptr);
    std::queue<std::shared_ptr<command_vrtp>> qu2;
    
    const std::chrono::time_point<std::chrono::steady_clock> trigger_Start2 = std::chrono::steady_clock::now();
    for(int64_t i = 0; i < 1; ++i)
    {
        memset(tArr2,0,sizeof(tArr2));
        tArr2[0] = 1;
        tArr2[2048] = 1;
      /*   qu2.push(cm_vrtp);
        //qu2.emplace(std::make_shared<generic_vrtp<dummyActor>>(ptr));
        auto front_value=std::move(qu2.front());
        qu2.pop();
        front_value->execute();*/
       //execute_cmd_vtrp(cm_vrtpview_2);
    }
    const auto diff2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - trigger_Start2);
    std::cout << diff2.count() << " ms\n";
   // std::cout << ptr->count << '\n';
    
    const auto vec = to_string("Hello", 1, 2.5);
    for(const auto& c : vec){
        std::cout << c << '\n';
    }
    
    std::cout << "orCombinator<isPtr,isConst>::lambda<int>::value " << orCombinator<isPtr,isConst>::lambda<int>::value << '\n';
    std::cout << "orCombinator<isPtr,isConst>::lambda<int>::value " << orCombinator<isPtr,isConst>::lambda<const int>::value << '\n';
    std::cout << "orCombinator<isPtr,isConst>::lambda<int>::value " << orCombinator<isPtr,isConst>::lambda<int* const>::value << '\n';
    
    /*
    template<template<typename> class predicate, class... list> 
struct all_same_pred;

template<template<typename> class predicate>
struct all_same_pred<predicate>{
    static const bool value = true;
};

template<template<typename> class predicate, typename head, typename... tail>
struct all_same_pred<predicate, head, tail...>{
  static const bool value = predicate<head>::value && all_same_pred<predicate, tail...>::value;
};*/

    
    std::cout << "all_same_pred<isPtr,int*,int*,int*>::value " << all_same_pred<isPtr,int*,int*,int*>::value << '\n';
    std::cout << "all_same_pred<isPtr,int,int,int,int>::value " << all_same_pred<isConst,const int,int,const int,const int>::value << '\n';
    
    
    std::cout << "fold_right " << fold_right<foldR,0,f_order,f_order,f_order,f_order>::value << '\n';
    
    std::cout << "sum " << sum_<1,2,3,4,5,6,7>::value << '\n';
    
    std::cout << "order " << order_<1,0,0>::value << '\n';
    
    std::cout << "len " << len_<1,0,0>::value << '\n';
    
    std::cout << "combine_ " << combine_<len_, order_ , 1,0,0>::value << '\n';
    
    //std::cout << "combine_ " << combine_<1,0,0>::value << '\n';
    
     std::cout << std::boolalpha;

  std::cout << "allVar(): " << allVar() << std::endl;
  std::cout << "all(): " << all() << std::endl;

  std::cout << "allVar(true): " << allVar(true) << std::endl;
  std::cout << "all(true): " << all(true) << std::endl;

  std::cout << "allVar(true, true, true, false): " << allVar(true, true, true, false) << std::endl;
  std::cout << "all(true, true, true, false): " << all(true, true, true, false) << std::endl;
     //std::cout << "combine_2 " << combine_<1,0,0>::value << '\n';
    
    auto o = Overloader{ [] (auto const& a) {std::cout << a << std::endl;},
                         [] (float f) {std::cout << std::setprecision(3) << f << std::endl;} };
    
    o("wtf");
   // kfr_test();
   
    std::vector<uint64_t> in{1, 4, 6, 89, 56, 45, 7};
    
    for(auto&& n : in | my_view::add_constant | view::take(100))
    {
        std::cout << n << ' ';
    }
    
    std::cout << std::endl;
    
    auto squares = view::transform(view::ints(0), [](int i){return i*i;});
    for(int i : squares | view::take(4))
        std::cout << i << ' ';
    
    std::cout << std::endl;
    return 0;
}
