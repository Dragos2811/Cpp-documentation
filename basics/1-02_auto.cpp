#include <iostream>
#include <vector>

using namespace std;

// auto: type deduction

int f() { return 10; }

void swap(int &a, int &b)
{
    auto tmp = a;
    a = b;
    b = tmp;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void g(auto i)
{
    cout << i << endl;
}

auto add(int a, int b)
{
    return a + b;
}

template<typename T, typename U>
auto divv(T t, U u) -> double
{
    if (u == 0)
        return -1.0;
    return t / u;
}

int main()
{
    auto name{"Ana"};
    auto i{f()};
    cout << i << endl;

    auto pi1{&i};  // int*
    cout << *pi1 << endl;

    auto *pi2{&i}, j{20};  // int
    cout << j << endl;

    vector<int> numbers{1, 2, 3, 4, 5};
    for (auto number : numbers)
        cout << number++;
    cout << endl;

     for (auto number : numbers)
        cout << number;
    cout << endl;

    for (auto &number : numbers)
        cout << number++;
    cout << endl;

    for (auto number : numbers)
        cout << number;
    cout << endl;

    auto x{10}, y{20};
    swap(x, y);
    cout << x << y << endl;

    //swap(&x, &y);
    cout << x << y << endl;

//    swap(nullptr, nullptr);

    int &xx{x};
//    int &yy{nullptr};


    g(19);

    cout << divv(10, 20) << endl;

    return 0;
}
