#include <iostream>
#include <initializer_list>
#include <vector>
#include <string>


using namespace std;


class MyContainer
{
public:
    MyContainer(string s) { cout << "ctor(s)" << endl; }
    MyContainer(initializer_list<string> elements) : m_elements(elements)  // call vector ctor
    {
//        for (auto e : elements)
//            m_elements.push_back(e);
    }

    friend ostream& operator<<(ostream &out, const MyContainer &c);

private:
    vector<string> m_elements;
};


ostream& operator<<(ostream &out, const MyContainer &c)
{
    for (auto e : c.m_elements)
        out << e << " ";
    return out;
}

struct A
{
    int m_i{};
    double m_d{};
};


int main()
{
    MyContainer c{"Ana", "Maria", "Ioana"};
    MyContainer c2{"Ana"};
    // A a {10, 20.0};
    cout << c << endl;
    cout << c2 << endl;

    return 0;
}
