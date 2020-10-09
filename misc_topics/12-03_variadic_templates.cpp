#include <iostream>
#include <string>
#include <vector>

using namespace std;


template <typename T>
void inc(T &t)
{
    ++t;
}

void process(){}

// variadic template example
template <typename T, typename ... Ts>
void process(T &head, Ts& ... ceilalti)
{
    inc(head);
    process(ceilalti...);
}

void test_process()
{
    auto d{2.2};
    auto f{1.34f};
    auto i{10};
    short s{12};
    process(d, f, i, s);
    process(d, s);
    process(d, i);
    cout << "d=" << d << " ";
    cout << "f=" << f << " ";
    cout << "i=" << i << " ";
    cout << "s=" << s << endl;
}

template <typename T>
int toint(T t)
{
//    static_assert(is_integral<T>()::value, "Not integral type");
    return static_cast<int>(t);
}

vector<int> process_bad()
{
    return vector<int>{};
}

template <typename T, typename ... Ts>
vector<int> process_bad(T head, Ts& ... other)
{
    vector<int> v;
    v.push_back(toint(head));
    vector<int> rest = process_bad(other...);
    v.insert(v.end(), rest.begin(), rest.end());
    return v;
}

template <typename ... Ts>
vector<int> process_good(Ts& ... args)
{
    return {toint(args)...};
}

void test_process_bad()
{
    auto d{2.2};
    auto f{1.34f};
    auto i{10};
    short s{12};
    vector<int> v {process_bad(d, f, i, s)};
    for (auto e : v)
        cout << e << " ";
    cout << endl;
}

void test_process_good()
{
    auto d{2.2};
    auto f{1.34f};
    auto i{10};
    short s{12};
    vector<int> v {process_good(d, f, i, s)};
    for (auto e : v)
        cout << e << " ";
    cout << endl;
}

int main()
{
   test_process();
   test_process_bad();
   test_process_good();

    return 0;
}
