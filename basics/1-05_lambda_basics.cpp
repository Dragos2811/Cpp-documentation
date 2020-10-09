#include <iostream>
#include <string>

using namespace std;

void greet(const string &name, void(*f)(const string &))
{
    if (f != nullptr)
        f(name);
}

int main()
{
    greet("ion", [](const string &name){
        cout << "Hello " << name << endl;
    });

    return 0;
}
