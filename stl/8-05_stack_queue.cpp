#include <iostream>
#include <stack>
#include <queue>

#include "person.h"

using namespace std;


int main()
{
    stack<Person> people;

    people.push(Person{"Ion", "Ionescu"});
    people.push(Person{"Pop", "Popescu"});
    people.push(Person{"Maria", "Marinescu"});
 
    Person p1 = people.top();
    people.pop();
    people.push(Person{"Cucu", "bau"});
    cout << p1 << endl;
 
 
    queue<Person> people2;  //(Person{"Alex", "IOnica"}, Person{"Ion", "IOnescu"});
    people2.push(Person{"Ion", "Ionescu"});
    people2.push(Person{"Pop", "Popescu"});
    people2.push(Person{"Maria", "Marinescu"});
 
    Person p2 = people2.front();
    people2.pop();
    cout << p2 << endl;
    
    deque<Person> people3;
    people3.push_front(Person{"Ion", "Ionescu"});
    people3.push_back(Person{"Maria", "Marinescu"});
    people3.push_front(Person{"Cici", "Ionescu"});
    
    for (auto e : people3)
        cout << e << endl;
 
    deque<Person> people4;
    do {
        Person p = people3.back();
        people4.push_back(p);
        people3.pop_back();
    } while(!people3.empty());

    for (auto e : people4)
        cout << e << endl;
    cout << people4.size() << endl;
    people4.pop_front();
    cout << people4.size() << endl;

    return 0;
}
