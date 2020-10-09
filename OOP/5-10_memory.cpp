#include <iostream>

using namespace std;


class my_vector
{
public:
    my_vector(size_t capacity) : m_capacity{capacity}
    {
        m_arr = new int[m_capacity]{};  // adresa e de pe HEAP!
    }

    ~my_vector() { cout << "dtor\n"; delete[] m_arr; }

    void add(int v)
    {
        if (m_size == m_capacity)
            double_capacity();
        m_arr[m_size++] = v;
    }

private:
    void double_capacity()
    {
        cout << "double cap\n";
        // 1. aloc memorie
        int *temp = new int[2 * m_capacity]{};
        // 2. copiez continutul actual in noua zona de memorie
        for (int i = 0; i < m_capacity; i++)
            temp[i] = m_arr[i];
        // 3. sterg zona veche
        delete[] m_arr;
        // 4. re-asignez m-arr catre zona noua
        m_arr = temp;
        m_capacity *= 2;
    }

    int *m_arr{};
    size_t m_size{};
    size_t m_capacity{};
};


int main()
{
    my_vector v{2};
    for (int i = 0; i < 256; i++)
        v.add(i);

    return 0;
}
