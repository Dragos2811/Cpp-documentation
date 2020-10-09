/*
se citeste de la tastatura nr de studenti
pentru fiecare student se citeste numele si nota
se insereaza toti studentii intr-un vector
cerinta: afisarea studentilor care au luat cele mai bune 2 note
*/

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const auto fname{ "students.txt" };

class student
{
public:
    student(string fn, string ln, unsigned int mark) :
        m_first_name{fn},
        m_last_name{ln},
        m_mark{mark}
    {}
    student() {}

    string get_name() const
    {
        return m_first_name + " " + m_last_name;
    }
    unsigned int get_mark() const { return m_mark; }

    bool operator<(const student &other)
    {
        return m_mark < other.m_mark;
    }

    bool operator==(const student &other)
    {
        return m_mark == other.m_mark;
    }

    bool operator>(const student &other)
    {
        return !operator<(other) && !operator==(other);
    }

    friend ostream &operator<<(ostream &out, const student &s);
    friend istream &operator>>(istream &in, student &s);
private:
    string m_first_name{};
    string m_last_name{};
    unsigned int m_mark{};
};

ostream &operator<<(ostream &out, const student &s)
{
    out << "Name: " << s.get_name();
    out << ". Mark: " << s.m_mark;
    return out;
}

istream &operator>>(istream &in, student &s)
{
    in >> s.m_first_name >> s.m_last_name >> s.m_mark;
    return in;
}

void test()
{
    vector<student>students;

    student ion{"Ion", "Ionescu", 10};
    students.push_back(ion);
    cout << ion << endl;

    student s;
    cout << "Introdu un student: ";
    cin >> s;
    students.push_back(s);

    bool mai_mic {ion < s && ion.operator<(s)};

    sort(students.begin(), students.end(),
         [&](auto a, auto b) { return a > b; });
    for (auto ss : students)
        cout << ss << endl;
}

int main()
{
    vector<student>students;
    ifstream f{ fname };
    if (!f.is_open()) {
        cerr << "Cannot open file\n";
        return -1;
    }
    student s;
    while (f >> s) {
        students.push_back(s);
    }

    sort(students.begin(), students.end(),
         [&](auto a, auto b) { return a > b; });

    cout << "All students:" << endl;
    for (auto s : students)
        cout << s << endl;

    cout << "Best students:" << endl;
    auto mark {students[0].get_mark()};
    int i {0};
    do {
        cout << students[i++] << endl;
    } while (i < students.size() && students[i].get_mark() == mark);

    if (i < students.size()) {
        mark = students[i].get_mark();
        do {
            cout << students[i++] << endl;
        } while (i < students.size() && students[i].get_mark() == mark);
    }

    return 0;
}
