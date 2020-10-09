/*
operator>
se citesc din people.txt
S Ion Ionescu 25 M 80 8 7 6 3 5
E Pop Popescu 30 M 80 10 10 9 8 10
P Vasile Ionescu 65 M 80 2000
M Andreea Ionescu 28 F 50 2000


operatii posibile (stdin)
    - afisarea tuturor studentilor (filtrare): show S
    - aflarea notei maxime pentru un student oarecare (ion ionescu): max
    - afisarea celor mai buni studenti (media cea mai mare): best
    - afisarea mediei generale pe toti studentii: avg
    - end => iesire din program
*/

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <numeric>

using namespace std;

enum class SEX {F, M};


SEX to_sex(const string &s)
{
    if (s == "M")
        return SEX::M;
    return SEX::F;
}

class Person;
class Student;
class Worker;
class Retiree;

class Operation
{
public:
    virtual void process(Person &p) = 0;
    virtual void process(Student &s) = 0;
    virtual void process(Worker &w) = 0;
    virtual void process(Retiree &r) = 0;
};

class Person
{
public:
    Person(string fn, string ln, unsigned age, SEX s, unsigned weight) :
        first_name{fn},
        last_name{ln},
        age{age},
        sex{s},
        weight{weight}
    {}
    Person(){}

    virtual ~Person() {}

    virtual bool operator>(const Person &o) const
    {
        return age > o.age;
    }
    virtual bool operator<(const Person &o) const
    {
        return age < o.age;
    }
    virtual bool operator==(const Person &o) const
    {
        return age == o.age;
    }

    string full_name() const { return first_name + " " + last_name; }

    friend istream &operator>>(istream &in, Person &p)
    {
        in>>p.first_name>>p.last_name>>p.age;
        string v; in >> v; p.sex = to_sex(v);
        return in >> p.weight;
    }

    friend ostream &operator<<(ostream &out, const Person &p)
    {
        out << p.str();
        return out;
    }

    virtual string str() const
    {
        stringstream ss;
        ss << first_name << " " << last_name;
        ss << ". age: " << age;
        ss << ". sex: " << [this](){ return sex == SEX::M ? "M" : "F"; }();
        ss << ". weight: " << weight;
        return ss.str();
    }

    virtual void set_operation(Operation *op) {this->op = op;}

    virtual void operate()
    {
        if (op != nullptr)
            op->process(*this);
    }

protected:
    string first_name{};
    string last_name{};
    unsigned age{};
    SEX sex {SEX::F};
    unsigned weight{};
    Operation *op{};
};

class Student : public Person
{
public:
    Student(string fn, string ln, unsigned age, SEX s, unsigned weight,
            const vector<unsigned> &marks) :
        Person(fn, ln, age, s, weight),
        marks{marks}
    {}
    Student(){}

    virtual ~Student() {}

    virtual double get_average() const
    {
        if (marks.size() == 0) return 0;
        auto sum {accumulate(marks.begin(), marks.end(), 0)};
        return sum / static_cast<double>(marks.size());
    }

    virtual bool operator>(const Person &o) const override
    {
        try {
            const Student &s{dynamic_cast<const Student&>(o)};
            return get_average() > s.get_average();
        } catch(...) {
            return Person::operator>(o);
        }
    }
    virtual bool operator<(const Person &o) const override
    {
        try {
            auto s{dynamic_cast<const Student&>(o)};
            return get_average() < s.get_average();
        } catch(...) {
            return Person::operator<(o);
        }
    }
    virtual bool operator==(const Person &o) const override
    {
        try {
            auto s{dynamic_cast<const Student&>(o)};
            return get_average() == s.get_average();
        } catch(...) {
            return Person::operator==(o);
        }
    }
    friend istream &operator>>(istream &in, Student &p)
    {
//        insert_common(in, p);
        in>>p.first_name>>p.last_name>>p.age;
        string v; in >> v; p.sex = to_sex(v);
        in >> p.weight;
        if (in) {
            unsigned mark;
            while(in >> mark)
                p.marks.push_back(mark);
        }
        return in;
    }

    virtual string str() const override
    {
        stringstream ss;
        ss << Person::str() << ". marks: ";
        for (auto mark : marks)
            ss << mark << " ";
        return ss.str();
    }

    virtual void operate() override
    {
        if (op != nullptr)
            op->process(*this);
    }

protected:
    vector<unsigned> marks;
};

class Retiree : public Person
{
public:
    Retiree(string fn, string ln, unsigned age, SEX s, unsigned weight,
            unsigned pension) :
        Person(fn, ln, age, s, weight),
        pension{pension}
    {}
    Retiree(){}
    virtual ~Retiree() {}

    friend istream &operator>>(istream &in, Retiree &p)
    {
//        insert_common(in, p);
        in >> p.first_name >> p.last_name>>p.age;
        string v; in >> v; p.sex = to_sex(v);
        in >> p.weight;
        return in >> p.pension;
    }

    virtual string str() const override
    {
        return Person::str() + ". pension: " + to_string(pension);
    }

    unsigned get_pension() const { return pension; }

    virtual void operate() override
    {
        if (op != nullptr)
            op->process(*this);
    }
protected:
    unsigned pension{};
};

class Worker : public Person
{
public:
    Worker(string fn, string ln, unsigned age, SEX s, unsigned weight,
           unsigned salary) :
        Person(fn, ln, age, s, weight),
        salary{salary}
    {}
    Worker() {}
    virtual ~Worker() {}

    virtual string str() const override
    {
        return Person::str() + ". salary: " + to_string(salary);
    }

    unsigned get_salary() const { return salary; }

    friend istream &operator>>(istream &in, Worker &p)
    {
//        insert_common(in, p);
        in>>p.first_name>>p.last_name>>p.age;
        string v; in >> v; p.sex = to_sex(v);
        in >> p.weight;
        return in >> p.salary;
    }

    virtual void operate() override
    {
        if (op != nullptr)
            op->process(*this);
    }
protected:
    unsigned salary{};
};

class TaxCollector: public Operation
{
public:
    virtual void process(Person &p) override
    {}
    virtual void process(Student &s) override
    {}
    virtual void process(Worker &w) override
    { tax += w.get_salary() * 0.5; }
    virtual void process(Retiree &r) override
    { tax += r.get_pension() * 0.4; }

    double get_tax() const { return tax; }
private:
    double tax{};
};

void process_commands(map<string, vector<Person*> > &people)
{
    string line;

    map<string, function<void(void)> > commands = {
        {"show", [&]() { for (auto p : people["S"]) cout << *p << endl; }},
        {"best1", [&]() {
            // varianta 1
            vector<Student*> students;
            for (auto p : people["S"]) {
                Student *s {dynamic_cast<Student*>(p)};
                if (s != nullptr)
                    students.push_back(s);
            }
            if (students.size() == 0)
                return;
            sort(students.begin(), students.end(),
            [&](auto a, auto b) { return a->get_average() > b->get_average(); });
            auto avg {students[0]->get_average()};
            for (auto s : students)
                if (s->get_average() == avg)
                    cout << *s << endl;
        }},
        {"best2", [&]() {
            sort(people["S"].begin(), people["S"].end(),
                [](auto a, auto b){return *a > *b;});
            for (int i = 0; i < 3 && i < people["S"].size(); i++)
                cout << *people["S"][i] << endl;
        }},
        {"collect_tax", [&]() {
            TaxCollector c;
            for (auto it : people)
                for (auto person : it.second) {
                    person->set_operation(&c);
                    person->operate();
                }
            cout << "Total tax: " << c.get_tax() << endl;
        }}
    };

    while (true) {
        cout << "Command: ";
        getline(cin, line);
        istringstream ss{line};
        string cmd;
        ss >> cmd;
        if (cmd == "end") break;
        auto it = commands.find(cmd);
        if (it != commands.end())
            it->second();
        else
            cout << "Unknown command\n";
    }
}

int main()
{
    const string fname{"people.txt"};
    ifstream f{fname};
    if (!f.is_open()) {
        cerr << "Cannot open file" << endl;
        return -1;
    }

    /*
    map<string, void(*)(Person&, const istream&)> factories {
        {"S", [](Student &s, const istream &is){ is >> s; }},
        {"P", [](Retiree &r, const istream &is){ is >> r; }},
        {"M", [](Worker &w, const istream &is){ is >> w; }},
        {"O", [](Person &p, const istream &is){ is >> p; }}
    };
    */

    map<string, vector<Person*> > people;
    string line;
    while (getline(f, line)) {
        istringstream ss{line};
        string type;
        ss >> type;
        if (type == "S") {
            Student *s = new Student{};
            ss >> *s;
            people["S"].push_back(s);
        } else if (type == "P") {
            Retiree *r = new Retiree{};
            ss >> *r;
            people["P"].push_back(r);
        } else if (type == "M") {
            Worker *w = new Worker{};
            ss >> *w;
            people["M"].push_back(w);
        } else if (type == "O") {
            Person *p = new Person{};
            ss >> *p;
            people["O"].push_back(p);
        }
    }

    process_commands(people);

    // free resources
    for (auto it = people.begin(); it != people.end(); it++)
        for (auto p : it->second)
            delete p;

    return 0;
}
