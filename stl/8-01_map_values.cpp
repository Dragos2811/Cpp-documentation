#include <iostream>
#include <string>
#include <map>

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
private:
    string m_first_name{};
    string m_last_name{};
};


int main()
{
    map<string, Person> ids;
    Person ion_ionescu{"Ion", "Ionescu"};
    ids.insert(make_pair("ionion", Person{"Ion", "Ion"}));
    ids.insert(make_pair("ionionescu", ion_ionescu));
    ids["cucu"] = Person{"Cucu", "Bau"};
    ids.emplace(make_pair("Take", Person{"Take", "Ionescu"}));

    auto i {ids.find("Take")};
    if (i != ids.end())
        ids.erase(i);
    
    for (auto it = ids.begin(); it != ids.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }

    cout << ids["ionion"] << endl;
    cout << ids.at("ionionescu") << endl;

    ids.clear();

    for (auto it = ids.begin(); it != ids.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }

    map<string, Person> ids2{
        {"ionion", Person{"Ion", "Ion"}},
        {"ionionescu", Person{"Ion", "Ionescu"}},
    };

    return 0;
}
