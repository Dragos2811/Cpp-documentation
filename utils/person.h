#pragma once

#include <iostream>
#include <string>


class Person
{
public:
    Person(std::string fn, std::string ln) :
        m_first_name{fn},
        m_last_name{ln}
    {}

    Person(){}

    Person(const Person& o) :
        m_first_name{o.m_first_name},
        m_last_name{o.m_last_name}
    {
        std::cout << "copy ctor for " << m_first_name << std::endl;
    }

    friend std::ostream &operator<<(std::ostream &out, const Person &p)
    {
        out << p.m_first_name << ", " << p.m_last_name;
        return out;
    }

    bool operator<(const Person &other) const
    {
        if (m_first_name < other.m_first_name)
            return true;
        return m_last_name < other.m_last_name;
    }
    bool operator==(const Person &other) const
    {
        std::cout << "==" << std::endl;
        return m_first_name == other.m_first_name && m_last_name == other.m_last_name;
    }
    bool operator>(const Person &other) const
    {
        return !operator==(other) && !operator<(other);
    }
private:
    std::string m_first_name{};
    std::string m_last_name{};
};
