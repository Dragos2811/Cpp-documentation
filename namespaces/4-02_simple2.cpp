#include <iostream>

using namespace std;

namespace Mordor
{
    int Wizard = -1;
}

namespace Shire
{
    int Wizard = 1;
    int Hobbit = 2;
}

void f()
{
    cout << "f" << endl;
}

namespace Mordor
{
    int Hobbit = -2;
}

int main()
{
    cout << Mordor::Wizard << endl;
    
    {
        using Shire::Wizard;
        cout << Wizard << endl;
        cout << Shire::Hobbit << endl;
        cout << Mordor::Wizard << endl;
    }
    
    using namespace Mordor;
    cout << Wizard << endl;
    cout << Hobbit << endl;
    
    return 0;
}

