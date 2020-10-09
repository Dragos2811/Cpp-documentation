#include <vector>
#include <string>
#include <iostream>
#include <thread>

using namespace std;

template<typename T>
void show_info(vector<T> &v)
{
    cout << "capacity: " << v.capacity() << endl;
    cout << "size: " << v.size() << endl;
    for (auto i : v)
        cout << i << " ";
    cout << endl;
}

void f()
{
    cout << "cucu bau" << endl;
}

int main()
{
    vector<int> v{1, 2, 3};
    v.push_back(4);

    show_info(v);
    vector<int> v2{1, 2, 3, 4, 5};
    v.insert(v.end(), v2.begin(), v2.end());
    show_info(v);

    vector<int> v3{10, 2};
    show_info(v3);

    vector<string> v4{10, "2"};

    vector<thread> workers;
    workers.emplace_back(thread{f});

    for (auto &w : workers)
        if (w.joinable())
            w.join();

    v4.resize(20);
    show_info(v4);

    v3.resize(100);
    show_info(v3);

    v3.swap(v);
    show_info(v3);

    cout << v3[1] << endl;

    return 0;
}
