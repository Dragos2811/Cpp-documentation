#include <iostream>

using namespace std;


namespace model
{
    class Person{};
    class Faculty{};
    class Student: public Person{};    
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

int main()
{
    using model::Person;
    /*model::*/Person p{};

}
