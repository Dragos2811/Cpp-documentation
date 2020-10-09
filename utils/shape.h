#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>


class Shape
{
public:
    Shape(int i) : m_i(i) {}
    Shape(int x, int y, std::string name) :
        m_x(x),
        m_y(y),
        m_name(name) {}

    virtual ~Shape() = default;

    virtual double area() const = 0;
    virtual double perimeter() const = 0;

    virtual void show() const
    {
        std::cout << "Shape::show() ";
        std::cout << m_name << ": (" << m_x << ", " << m_y << ")";
    }

    friend std::ostream& operator<<(std::ostream& out, const Shape& s)
    {
        out << s.m_name << ": (" << s.m_x << ", " << s.m_y << ")";
        return out;
    }

protected:
    int m_x{};
    int m_y{};
    std::string m_name{};

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
        std::cout << "Rectangle::show() ";
        std::cout << m_name << m_w << ", " << m_h << ": (" << m_x << ", " << m_y << ")" << std::endl;
    }

    virtual void specialRectangleFunction() const
    {
        std::cout << "Special Rectangle function" << std::endl;
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
        return std::acos(-1) * m_radius * m_radius;
    }

    virtual double perimeter() const override final  // not needed if class is final
    {
        return 2 * std::acos(-1) * this->m_radius;
    }

    virtual void show() const override final  // not needed if class is final
    {
        Shape::show();
        std::cout << "Radius: " << m_radius << std::endl;
    }

protected:
    int m_radius{};
};
