#include <iostream>

using namespace std;

namespace Mordor
{
    int Wizard = -1;
}

namespace Shire
{
    int Wizard = 1;
}

int main()
{
    cout << Mordor::Wizard << endl;
    
    {
        using namespace Shire;
        cout << Wizard << endl;
        cout << Mordor::Wizard << endl;
    }
    
    using namespace Mordor;
    cout << Wizard << endl;
    
    return 0;
}

