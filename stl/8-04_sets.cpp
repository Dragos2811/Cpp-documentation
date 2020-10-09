#include <iostream>
#include <string>
#include <set>

using namespace std;


int main()
{
    set<int> s1{1, 2, 3, 4, 5, 5, 5, 5, 10};
    s1.insert(100);
    
    for (auto number : s1)
        cout << number << " " << endl;
    
    auto key{4};
    if (s1.find(key) != s1.end())
        cout << key << " found" << endl;
    else
        cout << key << " not found" << endl;

    cout << s1.count(key) << endl;

    return 0;
}
