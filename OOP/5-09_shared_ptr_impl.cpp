#include <iostream>

using namespace std;

class A
{
public:
    A() { cout << "A()\n"; }
    ~A() { cout << "~A()\n"; }
};

class shared_ptr
{
public:
    shared_ptr(A *a) : a{a} { counter = new int{1}; }

    ~shared_ptr()
    {
        *counter = *counter - 1;
        if (*counter == 0) {
            if (a != nullptr) {
                delete a;
                a = nullptr;
            }
            if (counter != nullptr) {
                delete counter;
                counter = nullptr;
            }
        }
    }

    shared_ptr(const shared_ptr &o)
    {
        a = o.a;
        counter = o.counter;
        *counter = *counter + 1;
    }

private:
    int *counter{};
    A *a{};
};


void simple()
{
    A *a = new A{};
    shared_ptr s{a};
}

void complex()
{
    A *a = new A{};
    shared_ptr s1{a};
    shared_ptr s2{s1};
}

int main()
{
    simple();
    complex();

    return 0;
}
