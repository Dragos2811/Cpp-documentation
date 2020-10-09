#include <iostream>

using namespace std;


namespace model
{
    namespace people {
        class Person{};
        class Faculty{};
        class Student: public Person{};    
    }
}

namespace view
{
    class Entity{};
    class Person : public Entity{};
    class Faculty: public Entity{};
    class Student: public Person{};
    
    void show(Entity &e) {}
}

namespace controller
{

}

namespace mymodel = model::people;

int main()
{
    using mymodel::Person;
    Person p{};
    
    model::people::Faculty f1{};
    mymodel::Faculty f2{};

}

