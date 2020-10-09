// implement a simple container
// uses initializer list
// template class
// allows registration of callbacks when element is added / removed
//  on_add  => do somehting with T t
//  on_remove => do something with T t

#include <iostream>
#include <initializer_list>

using namespace std;

template <typename T>
class ring
{
public:
    ring(unsigned int capacity, std::initializer_list<T> elements) :
        m_capacity{capacity}
    {
        m_buf = new T[capacity];
        for (T e : elements)
            add(e);
    }
    
    ring(unsigned int capacity) : m_capacity{capacity}
    {
        m_buf = new T[capacity];
    }

    ring(const ring &other) : ring(other.m_capacity)
    {
        std::cout << "copy ctor" << std::endl;
        for (auto i = 0u; i < other.m_size; i++)
            add(other.m_buf[i]);
        m_pos = other.m_pos;
    }

    ring& operator=(const ring &other)
    {
        std::cout << "assignment op" << std::endl;
        m_size = 0;
        m_pos = 0;
        m_capacity = other.m_capacity;
        delete[] m_buf;

        m_buf = new T[other.m_capacity];
        for (auto i {0u}; i < other.m_size; i++)
            add(other.m_buf[i]);
        m_pos = other.m_pos;
        return *this;
    }

    virtual ~ring()
    {
        std:: cout << "dtor" << std::endl;
        delete[] m_buf;
    }
    
    void on_add(void(*f)(T))
    {
        m_on_add = f;
    }

    ring& add(T t)
    {
        m_pos = m_pos % m_capacity;
        m_buf[m_pos++] = t;
        m_size = (m_size < m_capacity) ? m_size + 1 : m_size;

        if (m_on_add != nullptr)
            m_on_add(t);

        return *this;
    }

    T get(unsigned int pos)
    {
        if (pos >= m_size)
            throw std::string("Invalid position");
        return m_buf[pos];
    }

    friend std::ostream &operator<<(std::ostream &out, const ring &r)
    {
        out << "Size = " << r.m_size << std::endl;
        out << "Capacity = " << r.m_capacity << std::endl;
        out << "Position = " << r.m_pos << std::endl;
        for (auto i = 0u; i < r.m_size; i++)
            out << r.m_buf[i] << std::endl;
        return out;
    }
    
    class iterator;
    
    iterator begin()
    {
        return iterator(0, *this);
    }
    iterator end()
    {
        return iterator(m_size, *this);
    }

private:
    unsigned int m_capacity{};
    unsigned int m_size{};
    unsigned int m_pos{};
    
    void (*m_on_add)(T){};
    void (*m_on_remove)(T){};
    
    T *m_buf{};
};


template <typename T>
class ring<T>::iterator
{
public:
    iterator(unsigned int pos, ring &r) :
        m_pos(pos),
        m_ring(r)
    {  // Empty
    }
    bool operator!=(const iterator &other)
    {
        return m_pos != other.m_pos;
    }
    bool operator==(const iterator &other)
    {
        return !operator!=(other);
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
    T operator*()
    {
        return m_ring.get(m_pos);
    }
private:
    unsigned int m_pos{};
    ring & m_ring;
};

void f(int a)
{
    cout << a << endl;
}

int main()
{
    ring<int> r{5};
    r.on_add([](int a) { cout << "Somebody added " << a << endl; });
    r.add(1).add(2).add(4);
    r.on_add(f);
    r.add(10).add(2);  
    
    for (auto e : r)
        cout << e << endl;

    return 0;
}
