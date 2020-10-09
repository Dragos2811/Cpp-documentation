#include <iostream>
#include <string>

using namespace std;


void test_basic()
{
    string s{"Ana are mere"};
    cout << s.substr() << endl;
    
    string fruct = s.substr(8, 4);
    cout << fruct << endl;
    
    cout << s.substr(1) << endl;
    string dup = s.substr(0, 3) + " " + s.substr(4, 3) + " pere";
    cout << dup << endl;
}

void test_find_substr()
{
    string s{"Ana are mere"};

    string fruit{"pere"};
    if (s.find(fruit) != string::npos) {
        cout << "Ana chiar are " << fruit << endl;
    } else {
        cout << "Ana nu are " << fruit << endl;
    }
}

void show_info(string& s)
{
    cout << "Length, size: " << s.size() << ", " << s.length() << endl;
    cout << "Is empty: " << (s.empty() ? "yes" : "no") << endl;
    cout << "Capacity: " << s.capacity() << endl;
    cout << "Max size: " << s.max_size() << endl;
}

void test_resize()
{
    string s{"content"};
    show_info(s);
    s.resize(100);
    cout << s << endl;
    show_info(s);

    s.reserve(0);
    show_info(s);
    s.clear();
    cout << "After clear:" << s << endl;
    show_info(s);
}

void test_str_as_array()
{
    string s{"content"};
    for (auto i = 0u; i < s.size(); i++) {
        s[i] = s[i] + 'A' - 'a';
    }
    cout << s << endl;
}

int main()
{
    test_basic();
    test_find_substr();
    string s{"Buna ziua"};
    show_info(s);
    test_resize();
    test_str_as_array();

    return 0;
}

