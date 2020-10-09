#include <iostream>
#include <string>

using namespace std;

void test_basic_usage()
{
    string ana = "Ana";
    string maria{"Maria"};
    string ionela("ionela");
    
    auto clone{ana};
    
    string s = clone + "B";
    cout << s << endl;
    
    s += " Ionescu";
    
    cout << s + string(clone) << endl;
}

void test_input()
{
    string sentence;
    cout << "Enter sentence:";
    cin >> sentence;
    cout << sentence << endl;

    getline(cin, sentence);
    cout << "Enter another sentence:";
    getline(cin, sentence);
    cout << sentence << endl;
}

// paul.ianas@edocti.com

void test_comparison()
{
    string s1, s2;
    cout << "Enter two sentences:";
    getline(cin, s1);
    getline(cin, s2);
    
    // method 1
    if (s1 == s2) {
        cout << "Equal sentences" << endl;
    } else if (s1 < s2) {
        cout << "s1 < s2" << endl;
    } else {
        cout << "s1 > s2" << endl;
    }
    
    // method 2
    int r {s1.compare(s2)};
    if (r == 0) {
        cout << "Equal sentences" << endl;
    } else if (r < 0) {
        cout << "s1 < s2" << endl;
    } else {
        cout << "s1 > s2" << endl;
    }
}

int main()
{
    test_basic_usage();
    test_input();
    test_comparison();

    return 0;
}

