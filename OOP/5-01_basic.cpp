#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Shape
{
public:
    Shape(int i) : m_i(i) {}
    Shape(int x, int y, string name) :
        m_x(x),
        m_y(y),
        m_name(name) {}

    Shape(const Shape& other) = delete;
//    {
//        cout << "Shape copy ctor" << endl;
//    }

    virtual double area() const = 0;  // { return 0;};
    virtual double perimeter() const = 0;  // {return 0;};

    virtual void show() const
    {
        cout << "Shape::show() ";
        cout << m_name << ": (" << m_x << ", " << m_y << ")" << endl;
    }

protected:
    int m_x{};
    int m_y{};
    string m_name{};

private:
    int m_i{};
};

class Rectangle : public Shape
{
public:
    Rectangle(int x, int y, int w, int h) :
        Shape(x, y, "Rectangle"),
        m_w(w),
        m_h(h)
    {  // Empty
    }

    Rectangle(int w, int h) :
        Rectangle(0, 0, w, h)  // delegating constructor
    {
        // init other member is needed (here)
    }

    virtual double area() const override
    {
        return m_w * m_h;
    }

    virtual double perimeter() const override
    {
        return 2 * (m_w + m_h);
    }

    virtual void show() const override
    {
        Shape::show();
        cout << "Rectangle::show() ";
        cout << m_name << m_w << ", " << m_h << ": (" << m_x << ", " << m_y << ")" << endl;
    }

protected:
    int m_w{};
    int m_h{};
};

int main()
{
    Rectangle r{0, 0, 100, 50};

    // slicing : DO NOT USE!!
    // Shape s3 = Rectangle(10, 10, 200, 200);  // upcast
    // s3.show();

    // C++ polymorphism works with 1) virtual functions and 2) pointers / references to objects
    Shape& s1 {r};
    s1.show();

    Shape *s2 {&r};
    s2->show();

    // here also copy ctor is called on Shape
//    vector<Shape> shapes;
//    shapes.push_back(Rectangle(10, 20, 100, 100));
//    shapes.push_back(Rectangle(30, 30, 100, 100));

//    shapes.emplace_back(Rectangle(10, 20, 100, 100));

//    for (auto s : shapes)
//        s.show();

    // we use pointers inside vector: polymorphism works!
    vector<Shape*> shapes_ok;
    shapes_ok.push_back(new Rectangle(10, 20, 100, 100));
    shapes_ok.push_back(new Rectangle(20, 30, 80, 100));

    for (auto s : shapes_ok)
        s->show();

    return 0;
}
