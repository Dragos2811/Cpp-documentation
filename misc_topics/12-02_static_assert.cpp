#include <iostream>
#include <string>

using namespace std;

class A
{
public:
    void f() { cout << "A::f()" << endl; }
};

template<typename T>
T factorial(T t) throw(string)
{
    static_assert(is_integral<T>::value, "Given type is not integral");
    // static_assert(t < 0, "t is not < 0");    

    if (t < 0)
        throw string("t cannot be < 0");
    
    T result = 1;
    while (t > 0) {
        result *= t--;
    }
    return result;    
}

template <typename T, typename U>
T sub(T t, U u)
{
    static_assert(sizeof(T) >= sizeof(U), "sizeof T > sizeof U");
    static_assert(is_arithmetic<T>() && is_arithmetic<U>(), "Not arithmetic types");
    return t - u;
}

struct Base
{
    virtual void f() const { cout << "Base:f()" << endl; }
    virtual ~Base() = default;
};

struct D1: public Base
{
    virtual void f() const override { cout << "D1::f()" << endl; }
    virtual ~D1() = default;
};

struct D2 : public D1
{
    void f() const override { cout << "D2::f()" << endl; }
    virtual ~D2() = default;
};

template <typename T>
void callF(T &t)
{
    static_assert(!is_abstract<T>(), "T cannot be abstract");
    static_assert(is_base_of<Base, T>(), "T is not derived from Base");
    t.f();
}

int main()
{
// error:
//    A a{};
//   A b {factorial(a)};

    cout << factorial(5) << endl;
    try {
        cout << factorial(-10) << endl;
    } catch(string &e) {
        cout << e << endl;
    }
    
    short s{10000};
    long long l{100000};
    
//    short s2{sub(s, l};
//    cout << sub(s, l) << endl;
    cout << sub(l, s) << endl;
//    cout << sub("ala", "bala") << endl;

    D1 d1{};
    callF(d1);
    
    A a{};
    callF(a);

    return 0;
}
