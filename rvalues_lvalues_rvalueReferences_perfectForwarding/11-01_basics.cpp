#include <iostream>
#include <string>
#include <vector>


using namespace std;


struct Base
{};

Base getBase()
{
    return Base{};
}


void test_basics()
{
    auto i{10};
    int *pi{&i};
    int **ppi{&pi};
    
    Base b{getBase()};  // b == lvalue
    // &getBase();  // rvalue <=> can't get address of it
    
    auto i2{i + 100};  // i + 100 = rvalue

    // wont' compile
    // auto i3{&i2++};  // i2 = &(i2+1)
    auto i3{&++i2};
}

void test_lvalue_reference()
{
    Base b1{};
    auto b2 = Base{};
    vector<Base> v{b1, b2, Base{}};
    
    Base &rb1{b1};

    // Base &rb3 {getBase()};  // warning: not guaranteed to work   
    const Base &rb3 {getBase()};
    auto rb4{getBase()};
    
    Base b5{getBase()};  // compiler ensures we don't "escape" the temp object!!
}

int main()
{
    test_basics();
    test_lvalue_reference();

    return 0;
}
