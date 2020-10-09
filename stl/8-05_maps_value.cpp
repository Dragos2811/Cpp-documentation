#include <map>
#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
    Person(string fn, string ln, int height) :
        first_name{fn}, last_name{ln}, height{height}
    {}

    Person(){}

    friend ostream &operator<<(ostream &out, const Person &p)
    {
        out << p.first_name << " " << p.last_name << ": " << p.height;
        return out;
    }


    bool operator<(const Person &o) const
    {
        return last_name < o.last_name;
    }

    bool operator==(const Person &o) const
    {
        return last_name == o.last_name;
    }

    bool operator>(const Person &o) const
    {
        return last_name > o.last_name;
    }

private:
    string first_name;
    string last_name;
    int height;
};


int main()
{
    map<int, Person> people {
        {10, Person{"Ion", "Ionescu", 185}},
        {20, Person{"Maria", "Marinescu", 168}},
        {30, Person{"Mirela", "Marinescu", 165}}
    };

    cout << people[20] << endl;


    map<Person, int> weights {
        {Person{"Ion", "Ionescu", 185}, 80},
        {Person{"Maria", "Marinescu", 168}, 60},
        {Person{"Mirela", "Marinescu", 165}, 60}
    };

    return 0;
}
