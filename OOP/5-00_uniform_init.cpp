#include <iostream>
#include <string>
#include <vector>
#include <map>


using namespace std;


struct position
{
    int x;
    int y;
    double d;
};

class S
{
public:
    int x;
    int y;
    double d;
};

class S2
{
public:
    S2(double d, int i) : m_d(d), m_i(i) {}
private:
    int m_i{};
    double m_d{};
};

void test_not_uniform()
{
    auto two = 2;
    auto three1(3);

    auto three{3};  // preferred way
    auto four = {4};

    position p1{2, 3, 3.0};
}


void test_uniform()
{
    position p1{2, 3, 3.0};
    S s{2, 10, 10.4f};
    S2 s2{2.3, 10};
    string greet{"Hello"};

    auto number{10};
    int *pnumber{&number};
    int *pn2{};  // nullptr
    int *pn3{nullptr};

    int numbers[]{1, 2, 3, 4, 5};
    int *pnumbers { new int[4]{1, 2, 3, 4} };
    cout << pnumbers[1] << endl;
    delete[] pnumbers;

    int ages[5]{};

    int mat[2][2]{ {1, 2}, {3, 4} };
    int mat2[2][2]{1, 2, 3, 4};

    struct {
        string name;
        int age;
    } ion{"Ion", 20};

    vector<string> names{"Ana", "Maria"};

    map<string, int> people{
        {"ion", 20},
        {"maria", 20}
    };

    // narrowing conversion prevention
    short ss{16000};
    ss += 36000;  // prevention off in this case

    // int i{10.0f};
    int i = 10.0f;
}


int main()
{
    test_not_uniform();
    test_uniform();

    return 0;
}
