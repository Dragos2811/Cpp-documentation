#include <iostream>

using namespace std;

namespace
{
    int Wizard = 10;
    float f = 100.2f;
}

namespace Shire
{
    int Wizard = 1;
    int Hobbit = 2;
}


int main()
{
    cout << Wizard << endl;
    cout << Shire::Wizard << endl;

    return 0;
}

