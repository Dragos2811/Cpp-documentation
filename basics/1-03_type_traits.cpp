#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;

template<typename T, typename U>
auto _div(T t, U u) -> decltype(t / u)
{
    if (u == 0)
        return -1.0;
    return t / u;
}


int main()
{
    string name;
    decltype(name) greet {"Hello world"};
    cout << "type of greet = " << typeid(greet).name() << endl;
    cout << "Greet: " << greet << endl;
    cout << "type of name = " << typeid(name).name() << endl;

    cout << _div(10, 20) << endl;
    cout << _div(10.2, 20) << endl;
    cout << _div(34.3f, 3.3f) << endl;

    return 0;
}
