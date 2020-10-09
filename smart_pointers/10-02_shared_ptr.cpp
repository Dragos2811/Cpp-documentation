#include <iostream>
#include <string>
#include <memory>

using namespace std;

class A
{
public:
    A(unsigned int x) : m_x{x} { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
    void show() const { cout << m_x << endl; }

private:
    unsigned int m_x{10900};
};

void f(shared_ptr<A> &pa)
{
    auto clone{pa};
    clone->show();
    cout << "inside f: usage count = " << pa.use_count() << endl;
}

void test_basic_usage()
{
    auto pa1{make_shared<A>(100u)};  // C++11
    shared_ptr<A> pa2{make_shared<A>(100u)};
    pa1->show();
    auto clone{pa1};
    cout << "test_basic_usage (before): usage count = " << pa1.use_count() << endl;
    f(pa1);
    cout << "test_basic_usage (after): usage count = " << pa1.use_count() << endl;
    
    shared_ptr<A> pa3{make_shared<A>(200u)};
    pa3.swap(pa1);
    pa3->show();
    pa1->show();
    clone->show();
    cout << "test_basic_usage (after swap): pa1 usage count = " << pa1.use_count() << endl;
    cout << "test_basic_usage (after swap): pa3 usage count = " << pa3.use_count() << endl;
}

void test_crack_ownership()
{ // DON'T
    A *a{new A{2000}};
    unique_ptr<A> ua{a};
    shared_ptr<A> sa1{a};
    
    sa1->show();
    cout << sa1.use_count() << endl;
    auto clone{sa1};
    ua->show();
    cout << sa1.use_count() << endl;

    ua.get()->show();
    ua.reset();
    cout << sa1.use_count() << endl;
    sa1->show();  // sigsegv (double delete)   
//    a->show();  
}


int main()
{
    test_basic_usage();
    test_crack_ownership();

    return 0;
}
