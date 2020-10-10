//
// Created by F93411C on 10/10/2020.
//
#include <iostream>

using namespace std;

class Person {
public:
    virtual void teach(){
      cout << "Person can teach" << endl;
    }
};

class Teacher: public Person{
public:
   virtual void teach() override {
      cout << "Teacher can teach in a school" << endl;
   }
};

int main()
{
    // C++ polymorphism works with 1) virtual functions and 2) pointers / references to objects
    Person person{}; //Person reference and object
    Teacher teacher{};

    Person& another_person{teacher}; //Person reference, Teacher object
    Teacher& another_teacher{teacher}; //Teacher reference and obj.

    person.teach();//output: Person can teach
    teacher.teach();//output: Teacher can teach in a school.

    // Here you can see Teacher object's method is executed even-though the Person reference was used
    another_person.teach();//output: Teacher can teach in a school

    teacher.teach();//output: Teacher can teach in a school
}