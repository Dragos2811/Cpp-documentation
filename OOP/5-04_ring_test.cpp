#include <iostream>
#include <string>

#include "shape.h"
#include "ring.h"

using namespace std;


void process(Shape& s)
{
    cout << endl;
    s.show();

    try {
        dynamic_cast<Rectangle&>(s).specialRectangleFunction();
    } catch(...) {
    }
}

void process(Shape* s)
{
    cout << endl;
    s->show();

    Rectangle *r =  dynamic_cast<Rectangle*>(s);
    if (r != nullptr)
        r->specialRectangleFunction();
}



int main(int argc, char** argv)
{
    ring<Shape*> shapes{4, {
        new Rectangle(0, 0, 100, 100),
        new Circle(10, 10, 20),
        new Rectangle(20, 20, 50, 100)
    }};

    shapes.add(new Circle(40, 40, 50));
    shapes.add(new Rectangle(100, 100, 20, 30));  // first position (0)
    shapes.add(new Circle(50, 40, 50));

    cout << shapes << endl;

    // old-school loop
    for (ring<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
        cout << **it << endl;

    for (auto s : shapes)
        cout << *s << endl;

    for (auto s : shapes) {
        process(*s);
        process(s);
    }

    return 0;
}
