#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct Base
{
    Base() { cout << "Base" << endl; }
    virtual ~Base() { cout << "~Base" << endl; }
    Base(Base &&other) noexcept { cout << "I am moved" << endl; }
    Base &operator=(Base &&other) noexcept {cout << "move assign" << endl; }
    Base &operator=(const Base &other) = default;
};

Base getBase()
{
    return Base{};
}

void f(const Base &b)
{
    cout << "f with lvalue ref" << endl;
}
void f(Base &&b)
{
    cout << "f with rvalue ref" << endl;
}

void g1(Base &&b)
{
    f(b);
}

void g2(Base &&b)
{
    f(static_cast<Base&&>(b));
}

void g3(Base &&b)
{
    f((Base&&)b);  // int(10.2f)
}

void g4(Base &&b)
{
    f(forward<Base>(b));
}

void test_rvalue_ref_basics()
{
    const Base &rb{getBase()};
    Base &&rrb{getBase()};
    
    f(rb);
    f(rrb);
    f(getBase());
}

void test_perfect_fwd()
{
    g1(getBase());
    g2(getBase());
    g3(getBase());
    g4(getBase());
}

template<typename T>
void swap2(T &a, T &b)
{
    T tmp{move(a)};
    a = move(b);
    b = move(tmp);
}

void test_swap()
{
    Base b1{}, b2{};
    swap2(b1, b2);
}

int main()
{
    test_rvalue_ref_basics();
    test_perfect_fwd();
    test_swap();
    
    return 0;
}
