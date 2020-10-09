#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;


class Person
{
public:
    Person(string fn, string ln) :
        m_first_name(fn),
        m_last_name(ln)
    {}
    bool operator<(const Person &o)
    {
        return m_last_name < o.m_last_name;
    }
    bool operator>(const Person &o)
    {
        return m_last_name > o.m_last_name;
    }
    bool operator==(const Person &o)
    {
        return m_last_name == o.m_last_name;
    }
    friend ostream &operator<<(ostream &out, const Person &p)
    {
        out << p.m_last_name << " " << p.m_first_name;
        return out;
    }
    string getFirstName() const { return m_first_name; }
    string getLastName() const { return m_last_name; }
private:
    string m_first_name{};
    string m_last_name{};
};

struct
{
    template<typename T>
    T operator()(T a, T b) { return a + b; }
} add_generic;

void lambda_internals()
{
    struct {
        int operator()(int a, int b) { return a + b; }
    } add;
    cout << add(10, 20) << endl;
    
    // <=> cu:
    auto add2 = [](int a, int b) { return a + b; };
    add2(10, 20);

    cout << add_generic(10, 20) << endl;
    cout << add_generic(10.23, 23.45) << endl;
}

int main()
{
    vector<Person> v {
        Person{"Ion", "Ionescu"},
        Person{"Ionica", "Ghica"},
        Person{"Alex", "Traian"}
    };

    sort(v.begin(), v.end(), [](auto p1, auto p2) { return p1 > p2; });
    for (auto &p : v)
        cout << p << endl;

    sort(v.begin(), v.end(),
         [](Person p1, Person p2){ return p1.getFirstName() > p2.getFirstName(); });
    for (auto &p : v)
        cout << p << endl;

    auto power = [](auto a, unsigned int b) {
        auto result {b == 0 ? 1 : a};
        for (auto i = 1u; i < b; i++) {
            result *= a;
        }
        return result;
    };
    
    cout << power(20, 3) << endl;
    cout << power(20.5, 3) << endl;
    cout << power(100.2, 0) << endl;
    cout << power(100.2, true) << endl;  // true becomes 1
    // not working:
    // cout << power(100.2, Person{"", ""}) << endl;

    lambda_internals();
    
    return 0;
}
