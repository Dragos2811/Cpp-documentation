#include <iostream>
#include <memory>

using namespace std;


class A
{
public:
    A() { cout << "A()\n"; }
    ~A() { cout << "~A()\n"; }
};


void intermediary()
{
    shared_ptr<A> arr[] = {
        make_shared<A>(),
        make_shared<A>(),
        make_shared<A>()
    };
    cout << "intermediary\n";
}


void g(int i)
{
    if (i == 0)
        throw 10;
    if (i == 1)
        throw "const char* exception";
}

void f(int i)
{
    // STACK UNWINDING
    shared_ptr<A> a1 {make_shared<A>()};
    A *a2{new A{}};
    A a3;
    cout << "before g\n";
    g(i);
    cout << "after g\n";
    A a4;
    delete a2;
}


int main()
{
    // intermediary();
    for (int i = 0; i < 1; i++)
        try {
            f(i);
        } catch (int &e) {
            cout << "int exc: " << e << endl;
        } catch (const char *e) {
            cout << "const char * exc: " << e << endl;
        } catch(...) {
            cout << "another exc\n";
        }

    return 0;
}
