#include <iostream>

using namespace std;

class A
{
public:
    A(int a, int b) : m_a{a}, m_b{b} {}
    void show() noexcept
    {
        auto c{30};
        auto d{m_a + m_b};
        //[this, c, d]() {
        //[=]() {
        [&, this]() {  // this must always be captured by value
            cout << ++m_a << endl;
            cout << m_b << endl;
            cout << c << endl;
            cout << d << endl;
        }();
    }
private:
    int m_a{};
    int m_b{};
};

int main()
{
    A a{10, 20};
    a.show();
    
    return 0;
}
