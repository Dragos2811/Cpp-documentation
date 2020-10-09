#include <iostream>
#include <map>
#include <string>

using namespace std;

class Person
{
public:
    Person(string fn, string ln) :
        m_first_name{fn},
        m_last_name{ln}
    {}

    Person(){}

    Person(const Person& o) :
        m_first_name{o.m_first_name},
        m_last_name{o.m_last_name}
    {
        cout << "copy ctor for " << m_first_name << endl;
    }

    friend ostream &operator<<(ostream &out, const Person &p)
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
        cout << "==" << endl;
        return m_first_name == other.m_first_name && m_last_name == other.m_last_name;
    }
    bool operator>(const Person &other) const
    {
        return !operator==(other) && !operator<(other);
    }
private:
    string m_first_name{};
    string m_last_name{};
};


int main()
{
    map<Person, int> ages {
        {Person{"Ion", "Ionescu"}, 25},
        {Person{"Marcel", "Pavel"}, 25},
    };
    
    
    for (auto it = ages.begin(); it != ages.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }
    
    Person cucu{"cucu", "rigu"};
    
    cout << ages[Person{"Ion", "Ionescu"}] << endl;
    cout << ages[cucu] << endl;
    
    ages[cucu] = 2;
    
    cout << ages[cucu] << endl;
    ages[cucu] = 10;
    cout << ages[cucu] << endl;
    
    return 0;
}
