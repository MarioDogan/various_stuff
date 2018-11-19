#ifndef COMMAND_H
#define COMMAND_H
#include <memory>
#include <vector>
#include <iostream>
#include <variant>
#include <queue>

template<typename T>
class command_crtp
{
public:
    void execute()
    {
        underlying().execute();
    }

private:
    T& underlying()
    {
        return static_cast<T&>(*this);
    }
    T const& underlying() const
    {
        return static_cast<T const&>(*this);
    }
};

template<typename T>
class generic_at_cmd_sink : public command_crtp<generic_at_cmd_sink<T>>
{
public:

    generic_at_cmd_sink(std::unique_ptr<T>&& actor):m_actor(std::move(actor)) {};
    void execute()
    {
        this->m_actor->execute();
    };

private:
    std::unique_ptr<T> m_actor;
};

template<typename T>
class generic_at_cmd : public command_crtp<generic_at_cmd<T>>
{
public:
    void setActor(std::shared_ptr<T>& actor){m_actor = actor;};
    void execute()
    {
        this->m_actor->execute();
    };

private:
    std::shared_ptr<T> m_actor;
};

template<typename T>
class generic_at_cmd_2 : public command_crtp<generic_at_cmd_2<T>>
{
public:
    void setActor(std::shared_ptr<T>& actor){m_actor = actor;}
    void execute()
    {
        this->m_actor->execute();
    };

private:
    std::shared_ptr<T> m_actor;
};

class generic_cmd_1 : public command_crtp<generic_cmd_1>
{
public:
    void execute()
    {
        std::cout << "generic_cmd_1\n";
    };
};

class generic_cmd_2 : public command_crtp<generic_cmd_2>
{
public:
    void execute()
    {
        std::cout << "generic_cmd_2\n";
    };
};

template<typename T>
struct SampleVisitor
{
    void operator()(generic_at_cmd<T>& cmd)
    {
         cmd.execute();
    }
    void operator()(generic_at_cmd_2<T>& cmd)
    {
        cmd.execute();
    }
};

template<typename T>
void execute_cmd(command_crtp<T>& l)
{
    l.execute();
}

template<typename T>
auto make_variant()
{
    std::variant<generic_at_cmd<T>, generic_at_cmd_2<T>> var;
    return var;
}

template<typename T>
auto make_variant_queue()
{
    std::queue<std::variant<generic_at_cmd<T>, generic_at_cmd_2<T>>> qu;
    return qu;
}

#endif // COMMAND_H
