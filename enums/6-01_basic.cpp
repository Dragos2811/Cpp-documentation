#include <iostream>

using namespace std;

enum DAYS {Mo=1, Tu, We, Th, Fr, Sa, Su};

enum E1 {A=1, B, C=1, D=0};

int main()
{
    cout << Mo << endl;
    cout << Tu << endl;

    cout << A << B << C << D << endl;

    E1 e1 = B;
    if (e1 == B) cout << "Indeed" << endl;

    if (e1 == 2) cout << "Also indeed" << endl;

    e1 = D;

    if (e1 == NULL) cout << "Hmmm" << endl;

    E1 e2 = static_cast<E1>(10);

    return 0;
}
