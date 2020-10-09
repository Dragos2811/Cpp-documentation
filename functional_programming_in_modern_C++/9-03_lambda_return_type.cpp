#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

int g{100};

auto f(int a, int b)
{
    return a + b;
}

auto runFun(double (*fun)(double, double), double a, double b)
{
    return fun(a, b);
}

template<typename T>
void do_something(T t, int a, int b)
{
    cout << "do_something" << endl;
    t(a, b);
    cout << typeid(t).name() << endl;
}

int main()
{
    auto d{10.0};
    auto i1{20};
    cout << [=](int a, int b){ return a + b + d; }(10, 20) << endl;
    cout << d << endl;
    auto fun = [](double a, double b) -> double {
        if (b == 0)
            return 0;
        return a / b;
    };

    double (*divide)(double a, double b) {fun};

    cout << [fun](double a, double b){ return fun(a, b); }(10, 20) << endl;
    cout << [divide](double a, double b) { return divide(a, b); }(10, 20) << endl;

    cout << [](double (*divide)(double a, double b), double a, double b) {
        return divide(a, b);
    }(divide, 10, 20) << endl;


    cout << f(10, 20) << endl;

    cout << runFun(fun, 10, 20) << endl;

    auto i{10};
    
    runFun([](double a, double b) ->double { return a + b; }, 10, 20);
    cout << i << endl;
    
    do_something([&i](int a, int b) { cout << "i=" << ++i << "a = " << a << endl; }, 10, 20);
    cout << i << endl;
    
    return 0;
}
