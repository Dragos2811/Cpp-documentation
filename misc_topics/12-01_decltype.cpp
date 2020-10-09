#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;


auto add(int a, double b) -> decltype(a + b)
{
    return a + b;
}

template<typename T, typename U>
auto f(T t, U u) -> decltype(t + u)
{
    if (t < u)
        return t + u;
    decltype(t + u) v = t * u;
    return t / u;  // forced to something like static_cast<decltype(t+u)>(t / u);
}


int main()
{
    string name{"Ion"};
    decltype(name) full_name{"Ion Ionescu"};  // string full_name{"dfsdfdsf"}
    
    cout << full_name << endl;
    cout << typeid(full_name).name() << endl;

    return 0;
}
