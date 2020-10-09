#include <iostream>
#include <string>

using namespace std;

void show_info(string& s)
{
    cout << "Length, size: " << s.size() << ", " << s.length() << endl;
    cout << "Is empty: " << (s.empty() ? "yes" : "no") << endl;
    cout << "Capacity: " << s.capacity() << endl;
    cout << "Max size: " << s.max_size() << endl;
    cout << &s << endl;
    const char *pc = s.c_str();
    cout << &pc << endl; 
}


void test_append()
{
    string s{"Ana are "};
    string news;
    news.append(s).append("mere");
    news.append(" si ");
    news.append(" pere. ");
    
    news.append(s.substr(4, 3));
    
    cout << news << endl;
    
    news.append(s, 4, 3);
    cout << news << endl;
    show_info(news);
    news.append(10000, '!');
    show_info(news);
    //cout << news << endl;
}

void test_append_char()
{
    string str;
    for (char c = 'A'; c <= 'z'; c++) {
        str.push_back(c);
    }
    cout << str << endl;
}

void test_assign()
{
    string s;
    s.assign(40, '!');
    cout << s << endl;
}

void test_insert()
{
    string quote {"to be"};
    quote.append(quote);
    quote.insert(5, " or not ");
    cout << quote << endl;
    test_assign();
}

void test_replace()
{
    string s {"Ana are mere"};
    string clone{s};
    string s2 {"pere portocale banane"};
    s.replace(8, 4, s2, 5, 9);
    
    string to_be_replaced{"mere"};
    string fruit{"portocale"};
    
    cout << s << endl;

    clone.replace(clone.find(to_be_replaced), to_be_replaced.size(), s2, s2.find(fruit), fruit.size());
    cout << clone << endl;
}



void test_erase()
{
    string s {"Ana are mere"};
    show_info(s);
    s.erase(4, 4);
    show_info(s);
}

void test_swap()
{
    string s1{"Mere"};
    string s2{"Pere"};
    show_info(s1);
    s1.swap(s2);
    show_info(s1);
    cout << s1 << endl;
    cout << s2 << endl;
}


int main()
{
//    test_append();
//    test_insert();
//    test_append_char();
//    test_replace();
//    test_erase();
    test_swap();

    return 0;
}

