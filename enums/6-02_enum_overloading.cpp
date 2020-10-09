#include <iostream>

using namespace std;

enum weekday {SUN, MON, TUE, WED, THU, FRI, SAT};

weekday operator+(weekday day, int days)
{
    return static_cast<weekday>((int(day) + days) % 7);
}


ostream &operator<<(ostream &out, weekday day)
{
    switch(day) {
    case SUN: out << "Sunday"; break;
    case MON: out << "Monday"; break;
    case TUE: out << "Tuesday"; break;
    case WED: out << "Wednesday"; break;
    case THU: out << "Thursday"; break;
    case FRI: out << "Friday"; break;
    case SAT: out << "Saturday"; break;
    default: out << "No idea"; break;
    }
    return out;
}

int main()
{
    weekday d = MON;

    d = d + 2;

    cout << d << endl;

    return 0;
}
