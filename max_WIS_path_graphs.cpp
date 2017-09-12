#include <iostream>
#include <vector>

using namespace std;

vector<int> computeMaxWIS(const vector<int> &w);
vector<int> solutionMaxWIS(const vector<int> &w);

int main()
{
    vector<int> w = {1, 4, 5, 4};
    vector<int> sol = solutionMaxWIS(w);
    vector<int> a = computeMaxWIS(w);

    for (auto i : sol)
        cout << i << " ";
    cout << endl;

    for (auto i : a)
        cout << i << " ";
    cout << endl;

    return 0;
}


vector<int> computeMaxWIS(const vector<int> &w)
{
    size_t n = w.size() + 1;
    vector<int> a(n);
    a[0] = 0;
    a[1] = w[0];

    for (size_t i = 2; i < n; ++i)
    {
        int S1 = a[i - 1];
        int S2 = a[i - 2] + w[i - 1];

        a[i] = S1 >= S2 ? S1 : S2;
    }

    return a;
}


vector<int> solutionMaxWIS(const vector<int> &w)
{
    vector<int> a = computeMaxWIS(w);
    vector<int> sol;
    
    size_t n = a.size();
    for (size_t i = n - 1; i > 0; --i)
    {
        if (a[i - 2] + w[i - 1] > a[i - 1])
        {
            sol.push_back(i - 1);
            --i;
        }
    }

    return sol;
}
