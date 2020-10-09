#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


class Shape
{
public:
    Shape(int i) : m_i(i) {}
    Shape(int x, int y, string name) :
        m_x(x),
        m_y(y),
        m_name(name) {}

    virtual ~Shape() = default;

    virtual double area() const = 0;
    virtual double perimeter() const = 0;

    virtual void show() const
    {
        cout << "Shape::show() ";
        cout << m_name << ": (" << m_x << ", " << m_y << ")";
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

    virtual ~Rectangle() = default;

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

class Circle final : public Shape
{
public:
    Circle(int x, int y, int radius) :
        Shape(x, y, "Circle"),
        m_radius(radius)
    {
    }

    virtual ~Circle() = default;

    virtual double area() const override
    {
        return acos(-1) * m_radius * m_radius;
    }

    virtual double perimeter() const override final  // not needed if class is final
    {
        return 2 * acos(-1) * this->m_radius;
    }

    virtual void show() const override final  // not needed if class is final
    {
        Shape::show();
        cout << "Radius: " << m_radius << endl;
    }

protected:
    int m_radius{};
};


//class CircleReinvented : public Circle
//{
//public:
//    CircleReinvented(int x, int y, int radius) : Circle(x, y, radius) {}

    // virtual double perimeter() const override { return Circle::perimeter(); }

    // virtual double area() const override { return Circle::area(); }
//};


int main()
{
    Rectangle r{0, 0, 100, 50};

    // C++ polymorphism works with 1) virtual functions and 2) pointers or references to objects
    Shape& s1 {r};
    s1.show();

    Shape *s2 {&r};
    s2->show();

    // we use pointers inside vector: polymorphism works!
    vector<Shape*> shapes_ok;
    shapes_ok.push_back(new Rectangle(10, 20, 100, 100));
    shapes_ok.push_back(new Rectangle(20, 30, 80, 100));
    shapes_ok.push_back(new Circle(20, 30, 80));
    shapes_ok.push_back(new Circle(20, 15, 100));

    for (auto s : shapes_ok)
        s->show();

    for (auto s : shapes_ok)
        delete s;

    return 0;
}
