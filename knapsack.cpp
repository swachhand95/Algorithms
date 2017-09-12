#include <iostream>
#include <vector>

using namespace std;

vector<int> solveKnapsack(const vector<int> &v, const vector<int> &w, 
        int cap, int &value);

void print(const vector<vector<int> > &v);

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int cap = 6;
    vector<int> v = {3, 2, 4, 4};
    vector<int> w = {4, 3, 2, 3};

    int value = 0;
    vector<int> items = solveKnapsack(v, w, cap, value);
    cout << value << endl;

    for (auto i : items)
        cout << i << " ";
    cout << endl;
}


vector<int> solveKnapsack(const vector<int> &v, const vector<int> &w, 
        int cap, int &value)
{
    vector<int> items;

    size_t n = v.size();
    vector<vector<int> > A(n + 1, vector<int>(cap + 1));

    for (size_t i = 1; i < A.size(); ++i)
    {
        for (size_t j = 0; j < A[i].size(); ++j)
        {
            int S1 = A[i-1][j];
            int S2 = 0;
            if (j >= w[i-1])
                S2 = A[i-1][j - w[i-1]] + v[i-1];
            A[i][j] = max(S1, S2);
        }
    }

    value = A[n][cap];

    int j = cap;
    for (size_t i = n; i > 0; --i)
    {
        if (A[i][j] != A[i-1][j])
        {
            items.push_back(i - 1);
            j = j - w[i-1];
        }
    }

    return items;
}


void print(const vector<vector<int> > &v)
{
    for (auto i : v)
    {
        for (auto j : i)
            cout << j << " ";
        cout << endl;
    }
}
