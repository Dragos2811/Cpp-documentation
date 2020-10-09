#pragma once
#include <iostream>
#include <initializer_list>
#include <vector>

template <typename T>
class matrix
{
public:
    matrix(int l, int c, std::initializer_list<T> elements) :
        m_lines(l),
        m_cols(c)
    {
        for (auto i = 0u; i < l; i++)
             m_mat.push_back(new T[m_cols]);

        int i{}, j{}, cnt{};
        for (T e : elements) {
            i = cnt / c;
            j = cnt % c;
            m_mat[i][j] = e;
            cnt++;
        }
    }

    matrix(unsigned int l, unsigned int c) : m_lines(l), m_cols(c)
    {
        for (auto i = 0u; i < m_lines; i++)
            m_mat.push_back(new T[m_cols]{});
    }

    matrix(const matrix& other) : m_lines(other.m_lines), m_cols(other.m_cols)
    {
        std::cout << "copy ctor" << std::endl;
        for (auto i=0u; i < m_lines; i++) {
            m_mat.push_back(new T[m_cols]);
            for (auto j = 0u; j < m_cols; j++)
                m_mat[i][j] = other.m_mat[i][j];
        }
    }

    matrix& operator=(const matrix &other)
    {
        std::cout << "assign op" << std::endl;
        m_lines = other.m_lines;
        m_cols = other.m_cols;
        for (auto i = 0u; i < m_lines; i++) {
            m_mat.push_back(new T[m_cols]);
            for (auto j = 0u; j < m_cols; j++)
                m_mat[i][j] = other.m_mat[i][j];
        }
        return *this;
    }

    virtual ~matrix()
    {
        for (auto i = 0U; i < m_lines; i++)
            delete[] m_mat[i];
    }

    bool operator==(const matrix& other)
    {
        if (m_lines != other.m_lines || m_cols != other.m_cols)
            return false;
        for (auto i = 0u; i < m_lines; i++)
            for (auto j = 0u; j < m_cols; j++)
                if (m_mat[i][j] != other.m_mat[i][j])
                    return false;
        return true;
    }

    bool operator!=(const matrix &other)
    {
        return !operator==(other);
    }

    friend std::ostream &operator<<(std::ostream& out, const matrix &m)
    {
        out << "Cols: " << m.m_cols << std::endl;
        for (auto i = 0u; i < m.m_lines; i++) {
            for (auto j = 0u; j < m.m_cols; j++)
                out << m.m_mat[i][j] << " ";
            out << std::endl;
        }
        return out;
    }

    matrix& operator+(const T &obj)
    {
        for(auto i = 0u; i < m_lines; i++)
            for (auto j = 0u; j < m_cols; j++)
                m_mat[i][j] = m_mat[i][j] + obj;  // operator+ needed for T
        return *this;
    }

    matrix& operator-(const T &obj)
    {
        for(auto i = 0u; i < m_lines; i++)
            for (auto j = 0u; j < m_cols; j++)
                m_mat[i][j] = m_mat[i][j] - obj;  // operator- needed for T
        return *this;
    }


    friend matrix operator+(const matrix &m1, const matrix &m2)
    {
        if (m1.m_lines != m2.m_lines || m1.m_cols != m2.m_cols)
            throw std::string{"Lines / cols do not match"};

        matrix m{m1.m_lines, m1.m_cols};
        for(auto i = 0u; i < m1.m_lines; i++)
            for (auto j = 0u; j < m1.m_cols; j++)
                m.m_mat[i][j] = m1.m_mat[i][j] + m2.m_mat[i][j];
        return m;
    }

    friend matrix operator-(const matrix &m1, const matrix &m2)
    {
        if (m1.m_lines != m2.m_lines || m1.m_cols != m2.m_cols)
            throw std::string{"Lines / cols do not match"};

        matrix m{m1.m_lines, m1.m_cols};
        for(auto i = 0u; i < m1.m_lines; i++)
            for (auto j = 0u; j < m1.m_cols; j++)
                m.m_mat[i][j] = m1.m_mat[i][j] - m2.m_mat[i][j];
        return m;
    }

    matrix& operator+=(const matrix& other)
    {
        for (auto i = 0u; i < m_lines; i++) {
            for (auto j = 0u; j < m_cols; j++)
                m_mat[i][j] += other.m_mat[i][j];
        }
        return *this;
    }

    matrix& operator-=(const matrix& other)
    {
        for (auto i = 0u; i < m_lines; i++) {
            for (auto j = 0u; j < m_cols; j++)
                m_mat[i][j] -= other.m_mat[i][j];
        }
        return *this;
    }

    matrix& operator+=(const T& obj)
    {
        for (auto i = 0u; i < m_lines; i++) {
            for (auto j = 0u; j < m_cols; j++)
                m_mat[i][j] += obj;
        }
        return *this;
    }

    matrix& operator-=(const T& obj)
    {
        for (auto i = 0u; i < m_lines; i++) {
            for (auto j = 0u; j < m_cols; j++)
                m_mat[i][j] -= obj;
        }
        return *this;
    }

    friend matrix operator+(const matrix &m1, const T &obj)
    {
        matrix m{m1.m_lines, m1.m_cols};
        for(auto i = 0u; i < m1.m_lines; i++)
            for (auto j = 0u; j < m1.m_cols; j++)
                m.m_mat[i][j] = m1.m_mat[i][j] + obj;
        return m;
    }

    friend matrix operator-(const matrix &m1, const T &obj)
    {
        matrix m{m1.m_lines, m1.m_cols};
        for(auto i = 0u; i < m1.m_lines; i++)
            for (auto j = 0u; j < m1.m_cols; j++)
                m.m_mat[i][j] = m1.m_mat[i][j] - obj;
        return m;
    }

    matrix& operator++(int)
    {
        operator+(1);
        return *this;
    }

    matrix& operator++()
    {
        operator+(1);
        return *this;
    }

    class iterator;

    iterator begin()
    {
        return iterator(0, *this);
    }

    iterator end()
    {
        return iterator(m_lines * m_cols, *this);
    }

private:
    std::vector<T*> m_mat{};
    unsigned int m_lines{};
    unsigned int m_cols{};
};

template<typename T>
class matrix<T>::iterator
{
public:
    iterator(unsigned int pos, matrix& m) :
        m_pos(pos),
        m_matrix(m)
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
        unsigned int i = m_pos / m_matrix.m_cols;
        unsigned int j = m_pos % m_matrix.m_cols;
        return m_matrix.m_mat[i][j];
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
    matrix& m_matrix{}; 
};
