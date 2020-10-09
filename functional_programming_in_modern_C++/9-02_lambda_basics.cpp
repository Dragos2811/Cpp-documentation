#include <iostream>
#include <string>

using namespace std;


void do_something(void (*operation)())
{
    operation();
}

template<typename T>
void do_something(T t, void (*operation)(T))
{
    operation(t);
}



int main()
{
    [](){};  // useless empty lambda; compiles in c++98 also
    
    auto l = [](){ cout << "Buna ziua" << endl; };
    l();

    [](string name){ cout << "Buna ziua, " << name << endl; }("Paul");
    
    do_something(l);

    auto greet = [](string name){ cout << "Buna ziua, " << name << endl; };
    do_something<string>("Paul", greet);

    do_something<int>(10, [](int i){ cout << i << endl; });
    
    auto l2 = [](int i){ return 2 * i; };
    cout << l2(4) << endl;
    cout << [](int i){ return 2 * i; }(4) << endl;

    int c{10}, d{20};
    [=, &c](){ c = c + 1; cout << c << ", " << d << endl; }();
    cout << c << endl;

    return 0;
}
