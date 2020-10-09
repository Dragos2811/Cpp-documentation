#pragma once

#include <iostream>
#include <initializer_list>

template <typename T>
class ring
{
public:
    ring(unsigned int capacity, std::initializer_list<T> elements) :
        m_capacity(capacity)
    {
        m_buf = new T[capacity];
        for (T e : elements)
            add(e);
    }

    ring(unsigned int capacity) : m_capacity(capacity)
    {
        m_buf = new T[capacity];
    }

    ring(const ring& other) : ring(other.m_capacity)
    {
        std::cout << "Inside copy ctor" << std::endl;
        for (auto i = 0u; i < other.m_size; i++) {
            add(other.m_buf[i]);
        }
        m_pos = other.m_pos;
    }

    ring& operator=(const ring& other)
    {
        std::cout << "Inside operator=" << std::endl;
        m_size = 0;
        m_pos = 0;
        delete[] m_buf;
        m_buf = new T[other.m_capacity];
        for (auto i = 0u; i < other.m_size; i++)
            add(other.m_buf[i]);
        return this;
    }

    virtual ~ring()
    {
        delete[] m_buf;
    }

    void add(T e)
    {
        m_pos = m_pos % m_capacity;
        m_buf[m_pos++] = e;
        m_size = (m_size == m_capacity) ? m_size : m_size + 1;
    }

    T get(unsigned int i) const
    {
        if (i >= m_capacity) {
            throw std::string{"Index out of range"};
        }
        return m_buf[i];
    }

    friend std::ostream& operator<<(std::ostream& out, const ring& r)
    {
        out << "size = " << r.m_size;
        out << "; pos = " << r.m_pos;
        out << "; capacity = " << r.m_capacity << std::endl;
        for (auto i = 0u; i < r.m_size; i++)
            out << r.m_buf[i] << std::endl;
        return out;
    }

    unsigned int size() const { return m_size; }

    class iterator;

    iterator begin()  // new instance of iterator!!
    {
        return iterator(0, *this);
    }

    iterator end()  // new instance
    {
        return iterator(m_size, *this);
    }

private:
    unsigned int m_capacity{};
    unsigned int m_size{};
    unsigned int m_pos{};

    T* m_buf{};  // nullptr
};

template <typename T>
class ring<T>::iterator
{
public:
    iterator(unsigned int pos, ring& r) :
        m_pos(pos),
        m_ring(r)
    {  // empty
    }

    virtual ~iterator() = default;

    bool operator!=(const iterator& other)
    {
        return m_pos != other.m_pos;
    }

    bool operator==(const iterator& other)
    {
        return !operator!=(other);
    }

    T operator*()
    {
        return m_ring.get(m_pos);
    }

    iterator& operator++(int)
    {
        m_pos++;
        return *this;
    }

    iterator& operator++()
    {
        m_pos++;
        return *this;
    }

private:
    unsigned int m_pos{};
    ring& m_ring{}; 
};
