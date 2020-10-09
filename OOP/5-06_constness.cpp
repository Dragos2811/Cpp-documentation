#include <iostream>
#include <string>

using namespace std;

class A
{
public:
    A(int x) : x{x} {}
    void show() const { cout << x << endl; }
    void set_x(int x) { this->x = x; }
private:
    int x{};
};

void f(const A &a, int x)
{
    // won't compile: set_x is not const!!!
    // a.set_x(x);
}

// won't compile: const is applied on *this
// not on external function
//void g() const
//{}


int main()
{
    A a{10};
    a.show();
    f(a, 20);
    a.show();

    return 0;
}
