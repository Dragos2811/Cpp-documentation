#include <iostream>

using namespace std;

// before being able to use it from main,
// we need to declare it first. We can define it afterwards
double square(double);


int main()
{
    cout << square(100) << endl;
    return 0;
}

double square(double x)
{
    return x * x;
}
