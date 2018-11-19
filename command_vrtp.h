#ifndef COMMAND_VRTP_H
#define COMMAND_VRTP_H
#include <memory>
#include <vector>
#include <iostream>
#include <variant>
#include <queue>

class command_vrtp
{
public:
    virtual void execute() = 0;
    virtual ~command_vrtp(){};
};

template<typename T>
class generic_vrtp : public command_vrtp
{
public:
    generic_vrtp() = default;
    explicit generic_vrtp(std::shared_ptr<T>& actor):m_actor(actor){};
    
    void setActor(std::shared_ptr<T>& actor){m_actor = actor;};
    virtual void execute() noexcept override  
    {
        this->m_actor->execute();
    };

private:
    std::shared_ptr<T> m_actor{0};
};

void execute_cmd_vtrp(command_vrtp& cmd)
{
    cmd.execute();
}

#endif // COMMAND_VRTP_H
