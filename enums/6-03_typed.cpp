#include <iostream>

using namespace std;

enum class weekday {SUN=1, MON, TUE=1, WED, THU, FRI, SAT};

enum class Planet {Mercur, Venus, Pamant};

enum e1 {A, B, C};
enum e2 {AA, BB, CC};

class A{};


int main()
{
    weekday d {weekday::SUN};
    //if (d == 0) cout << "Indeed" << endl;

    weekday d2 {weekday::MON};

    if (d == d2) cout << "Match" << endl;

    switch (d) {
    case weekday::SUN: cout << "Sunday" << endl; break;
    case weekday::MON: cout << "Sunday" << endl; break;
    default: cout << "Don't care" << endl; break;
    }

/*    e1 v1 = A;
    e2 v2 = AA;

    if (v1 == v2);
  */  
    Planet noi {Planet::Pamant};

   // if (noi == weekday::TUE) { cout << "Bad" << endl; }

    if (weekday::SUN == weekday::TUE) cout << "Equal" << endl;

    return 0;
}
