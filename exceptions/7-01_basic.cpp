#include <iostream>
#include <string>

using namespace std;


class A
{
public:
    A() { cout << "A()" << endl; }
    virtual ~A() { cout << "~A()" << endl; } 
    void show() { cout << "A::show()" << endl; }       
};


void usually_throws(int i)
{
    if (i < 3)
        throw 12;
    else if (i >=3 && i < 7)
        throw "Const char* exception";
    else
        throw string{"string exception"};    
}


void intermediar(int i)
{
    A a{};
    usually_throws(i);
    a.show();    // stack unwinding... objects created in between are destroyed
    cout << "Returning" << endl;
    return;
}


int main()
{
    for (int i = 0; i < 10; i++) {
        try {
            intermediar(i);
        } catch(int e) {
            cout << "Caught " << e << endl;
        } catch(char const *e) {
            cout << "Caught " << e << endl;
        } catch(string &e) {
            cout << "Caught " << e.c_str() << endl;
        } catch(...) {
            cout << "Caght something else" << endl;
        }
    }

    return 0;
}

