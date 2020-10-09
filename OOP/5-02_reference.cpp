#include <iostream>

using namespace std;

int c {100};

void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;

    a = c;  // no way to modify the address of a
}


int main()
{
    int a{10}, b{20};

    cout << &a << ": " << a << endl;
    swap(a, b);
    cout << &a << ": " << a << endl;

    return 0;
}
