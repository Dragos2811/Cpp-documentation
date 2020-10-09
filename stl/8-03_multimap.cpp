#include <iostream>
#include <map>
#include <string>

using namespace std;


int main()
{
    multimap<int, string> dictionar{
        {1, "str1"},
        {2, "str2"},
        {3, "str3"},
        {1, "str4"},
        {1, "str5"}
    };

    cout << "list all: " << endl;
    for (auto e : dictionar) {
        cout << e.first << ": " << e.second << endl;
    }
    
    // wrong way of doing this
    for (auto it = dictionar.find(1); it != dictionar.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }

    // right way
    pair<multimap<int, string>::iterator, multimap<int, string>::iterator> fp = dictionar.equal_range(1);
    
    for (auto it = fp.first; it != fp.second; ++it) {
        cout << it->first << ": " << it->second << endl;
    }

    pair<int, int> my_pair{10, 20};
    cout << my_pair.first << endl;
    cout << my_pair.second << endl;

    return 0;
}
