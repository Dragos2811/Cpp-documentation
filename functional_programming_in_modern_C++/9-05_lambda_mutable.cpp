#include <iostream>
#include <string>

using namespace std;


void test_mutable_scope()
{
    auto i{10};
    
    auto f = [i]() mutable {
        i += 5;  // scope of i is maintained between multiple lambda calls
        cout << "lambda scope: i = " << i << endl;
    };
    
    f();
    f();
    
    cout << "outer scope: i = " << i << endl;
}

void test_unmutable()
{
    auto i {10};  // must be initialized!!
    //i++;
    
    auto f = [i]() {
        cout << "lambda scope: i = " << i << endl;
    };
    i += 5;
    f();
    cout << "outer scope: i = " << i << endl;

    i += 5;
    f();
    cout << "outer scope: i = " << i << endl;

    i += 5;
    f();
    cout << "outer scope: i = " << i << endl;

}

int main()
{
    test_mutable_scope();
    test_unmutable();
    
    return 0;
}
