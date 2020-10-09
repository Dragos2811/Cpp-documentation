#include <iostream>
#include <string>

#include "matrix.h"

using namespace std;

int main()
{
    matrix<int> m1{2, 2, {1, 9, 3, 4}};
    matrix<int> m2{2, 2, {5, 7, 2, 4}};

    auto m3 {m1 + m2};
    cout << m3 << endl;
    auto m4 {m1 - m2};
    cout << m4 << endl;

//    auto m5 {m1 * 2};

    m1 -= 1;
    cout << m1 << endl;
//     auto m6 {m1 - 1};
    //cout << m6 << endl;
    cout << m1 << endl;

    matrix<int> m7{m2};
    cout << m7 << endl;
    m7 -= m1;
    cout << m7 << endl;

    m7 += m1;
    cout << m7 << endl;
    cout << "cucu" << endl;

    cout << m1 << endl;
    m7 = m1 - 1;
    cout << m7 << endl;
    m7 = m7 + 1;
    cout << m7 << endl;

    for (auto e : m1)
        cout << e << " ";
    cout << endl;

    matrix<string> m8{2, 3, {"A", "B", "C", "D", "E", "F"}};
    cout << m8 << endl;
    for (auto e : m8)
        cout << e << " ";
    cout << endl;

    cout << m7++ << endl;
    cout << ++m7 << endl;

    return 0;
}
