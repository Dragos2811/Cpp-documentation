#include <iostream>
#include <vector>

using namespace std;


vector<vector<int> > generate(int n)
{
    vector<vector<int> > v;
    for (int i = 1; i <= n; i++) {
        vector<int> vv(i, i);
        v.push_back(vv);
    }
    return v;
}

void generate_vector(int cols, vector<int> &v)
{
    for (int i = 0; i < cols; i++)
        v.push_back(i);
}

void generate_triangle(int rows, vector<vector<int> >&v)
{
    for (int i = 1; i <= rows; i++) {
        vector<int> row;
        generate_vector(i, row);
        v.push_back(row);
    }
}

void display(vector<vector<int> > &mat)
{
    for (auto line : mat) {
        for (auto e : line)
            cout << e << " ";
        cout << endl;
    }
}

void add1(vector<vector<int> > &t1, vector<vector<int> >&t2,
          vector<vector<int> >&result)
{
    for (int i = 0; i < t1.size(); i++) {
        result.push_back(vector<int>(i+1));
        for (int j = 0; j < t1[i].size(); j++) {
            result[i][j] = t1[i][j] + t2[i][j];
        }
    }
}

void add2(vector<vector<int> > &t1, vector<vector<int> >&t2,
          vector<vector<int> >&result)
{
    for (int i = 0; i < t1.size(); i++) {
        result.push_back(vector<int>(i+1));
        auto &v1 { t1[i] };
        auto &v2 { t2[i] };
        auto &r { result[i] };
        for (int j = 0; j < v1.size(); j++)
            r[j] = v1[j] + v2[j];
    }
}

int main()
{
    auto v {generate(10)};
//    display(v);

    vector<vector<int> > t1;
    generate_triangle(5, t1);
    vector<vector<int> > t2;
    generate_triangle(5, t2);
    vector<vector<int> > result;
    display(t1);
    display(t2);

    add1(t1, t2, result);
    display(result);

    return 0;
}
