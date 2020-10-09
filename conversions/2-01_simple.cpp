#include <iostream>
#include <string>

using namespace std;

class Animal
{
public:
    Animal(string name) : m_name(name) {};
    virtual ~Animal() = default;
    virtual void speak() const = 0;
    virtual void change_name(string name) { m_name = name; }
private:
    string m_name{};
};

class Dog: public Animal
{
public:
    Dog(string name) : Animal(name) {}
    virtual ~Dog() = default;
    virtual void speak() const override { cout << "Ham!" << endl;}
    virtual void bark() const { speak(); }
};

class Cat: public Animal
{
public:
    Cat(string name) : Animal(name) {}
    virtual ~Cat() = default;
    virtual void speak() const override { cout<< "Miau!"<<endl; }  
    virtual void miau() const { speak(); }
};

class Oarecare
{
public:
    void show() const { cout << m_i << endl; }
private:
    int m_i{1000};
};

float f()
{
    return -1;
}


void test_implicit()
{
    int i = 1;
    short s = 2;
    long l = 3;
    float f = 1.3f;
    double d = 0.1;

    i = i + s;  // promotion
    if (d)
        cout << d << endl;

    d = 2 * f;

    s = i + 35000;
    cout << s << endl;
}

void test_narrowing()
{
    short s{16000};
    s += 36000;
    cout << s << endl;

    // int i {10.0f};
    int j = 10.0f;
    int k{};
    string sstr{};
    cout << k << endl;
    cout << sstr << endl;
    if (sstr == "")
        cout << "empty" << endl;
    int* pint = new int(10);
    cout << pint << endl;
    delete pint;
    pint = nullptr;
    delete pint;
}

void types_of_conv()
{
    int j{10};

    short s1 = (short)j;
    short s2 = short(j);
    cout << s2 << endl;

    short s3 = static_cast<short>(j);

    float f{12.3f};
    int *pf = (int*)&f;
    //int *pf1 = static_cast<int*>(&f);

    Dog nero{"Nero"};
    Animal *pnero = &nero;
    // Oarecare* pdog  = static_cast<Oarecare*>(pnero);
    // Oarecare *po = (Oarecare*)pnero;

    void *pvoid = static_cast<void*>(&f);
    void *pvdog = static_cast<void*>(pnero);

    int *pint = static_cast<int*>(pvoid);
    int *pint2 = (int*)pnero;  // compiler ok, but... not ok

    cout << s3 << endl;
}


void test_dynamic_cast()
{
    Dog nero{"Nero"};
    Animal *pnero = &nero;
    Dog *pdog {dynamic_cast<Dog*>(pnero)};
    if (pdog != 0) {
        cout << "Successfull conversion" << endl;
        pdog->bark();
        // pnero->bark();
    } else {
        cout << "Not a dog" << endl;
    }

    Cat *pcat = dynamic_cast<Cat*>(pnero);
    if (pcat != nullptr) {
        pcat->miau();
    } else {
        cout << "Unsuccessful conversion" << endl;
    }
}

struct A
{
    int m_i{1000};
    float m_f{1000.0f};
};

struct B
{
    int m_ii{2000};
    float m_ff{2000.0f};
};

void test_reinterpret_cast()
{
    Dog nero{"Nero"};
    Animal *pnero = &nero;
    auto pdog{&nero};

    Oarecare* po = reinterpret_cast<Oarecare*>(pdog);
    po->show();

    A a;
    B *pb = reinterpret_cast<B*>(&a);
    cout << pb->m_ff << endl;
}



int main()
{
    test_implicit();
    test_narrowing();
    types_of_conv();
    test_dynamic_cast();
    test_reinterpret_cast();

    return 0;
}
