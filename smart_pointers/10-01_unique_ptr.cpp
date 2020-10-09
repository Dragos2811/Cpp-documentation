#include <iostream>
#include <string>
#include <memory>

using namespace std;


class A
{
public:
    A(unsigned int x) : m_x{x} { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
    void show() const { cout << 100 / m_x << endl; }

private:
    unsigned int m_x{10900};
};


void test_basic_usage()
{
    unique_ptr<A> pa1{make_unique<A>(30)};
    unique_ptr<A> pa2{new A{40}};
    A *pa3{new A{50}};
    pa1->show();
    pa2->show();
    pa3->show();

    // obtain raw ptr
    A *raw2{pa2.get()};
    raw2->show();

    unique_ptr<A> pa4{move(pa2)};
    pa4->show();
    // pa2->show();  // sigsegv!!

    A *pa5{new A{60}};
    unique_ptr<A> pa6{pa5};
    unique_ptr<A> pa7{move(pa6)};
    delete pa5;
    cout << "cucu";
    pa7->show();
//    pa6->show();

    delete pa3;
}

void special_requests()
{
    A *a{new A{100}};
    unique_ptr<A> pa{a};
    unique_ptr<A*> ppa{&a};
    // *(*(ppa + l) + c) =  ...   
}

unique_ptr<A> stupid_test()
{
    A *a{new A{60}};
    unique_ptr<A> pa{a};
    auto a2{pa.get()};
    cout << "a.show(): ";
    a->show();
    cout << (a == a2) << endl;
    return pa;
}

int main()
{
    unique_ptr<int> pi{new int{10}};
    *pi += 7;
    cout << *pi << endl;
    
//    unique_ptr<A> pa {make_unique<A>(20)};  // C++14, make_shared (C++11)
//    pa->show();
    
    test_basic_usage();

    unique_ptr<A> pa {stupid_test()};
    pa->show();

    special_requests();

    return 0;
}
