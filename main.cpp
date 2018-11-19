#include <stdio.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <chrono>
#include "command.h"
#include "command_vrtp.h"
#include <cstring>
#include "template_play.h"

class dummyActor{
public:
    void execute(){count += count * 2;}
    uint64_t count{1};
};

class dummyActor2{
public:
    void execute(){std::cout << "execute dummyActor 2\n";}
};

int test(const int num1, const int num2, const int num3) {
    std::cout << "num1 " << num1 <<'\n';
    std::cout << "num2 " << num2 <<'\n';
    std::cout << "num3 " << num3 <<'\n';
    return 0;
}

uint8_t tArr2[4096] = {0};

int main(int argc, char **argv)
{
    auto ptr = std::make_shared<dummyActor>();
    generic_at_cmd_sink cmd1{std::make_unique<dummyActor>()};
    generic_at_cmd_sink cmd2{std::make_unique<dummyActor2>()};
    generic_at_cmd<dummyActor> cmd3;
    generic_at_cmd_2<dummyActor> cmd5;
    SampleVisitor<dummyActor> visit;
    auto qu = make_variant_queue<dummyActor>();
    auto var = make_variant<dummyActor>();
    cmd3.setActor(ptr);
    cmd5.setActor(ptr);
    var = cmd3;
    int i = 0;
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
    /*    qu2.push(cm_vrtp);
        //qu2.emplace(std::make_shared<generic_vrtp<dummyActor>>(ptr));
        auto front_value=std::move(qu2.front());
        qu2.pop();
        front_value->execute();*/
       //execute_cmd_vtrp(cm_vrtp_2);
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
	return 0;
}
