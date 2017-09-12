#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;

#define SIZE 875715

void get_input(const string& filename, int sz, vector<vector<int>>& g,
    vector<vector<int>>& g_rev)
{
    ifstream fin(filename);
    if (!fin.is_open())
        return;

    string line;
    vector<vector<int>> G(sz);
    vector<vector<int>> Grev(sz);
    while (getline(fin, line))
    {
        stringstream ss(line);
        int u = 0, v = 0;
        ss >> u >> v;
        G[u - 1].push_back(v - 1);
        Grev[v - 1].push_back(u - 1);
    }

    g = G;
    g_rev = Grev;

    fin.close();
}

void dfs1(const vector<vector<int>>& G, int s, bool* explored, int* f, int& t)
{
    explored[s] = true;
    // cout << s << " ";

    for (int i = 0; i < G[s].size(); ++i)
        if (!explored[G[s][i]])
            dfs1(G, G[s][i], explored, f, t);

    f[s] = t++;
}

void dfsLoop1(const vector<vector<int>>& G, int* f)
{
    int t = 0;
    memset(f, 0, sizeof f);

    bool* explored = new bool[G.size()];
    memset(explored, 0, sizeof explored);

    for (int i = G.size() - 1; i >= 0; --i)
        if (!explored[i])
            dfs1(G, i, explored, f, t);

    delete []explored;
}

void dfs2(const vector<vector<int>>& G, int s, bool* explored, vector<int>& leaders, int l, int* f)
{
    explored[s] = true;
    leaders[s] = l;

    for (int i = 0; i < G[s].size(); ++i)
        if (!explored[G[s][i]])
            dfs2(G, G[s][i], explored, leaders, l, f);

}

vector<int> dfsLoop2(const vector<vector<int>>& G, int* f, int& cnt)
{
    cnt = 0;

    vector<vector<int>> newG(G.size());
    for (int i = 0; i < newG.size(); ++i)
    {
        vector<int> adj;
        for (int j = 0; j < G[i].size(); ++j)
            adj.push_back(f[G[i][j]]);
        newG[f[i]] = adj;
    }

    vector<int> leaders(newG.size());

    bool* explored = new bool[newG.size()];
    memset(explored, 0, sizeof explored);

    for (int i = newG.size() - 1; i >= 0; --i)
    {
        if (!explored[i])
        {
            dfs2(newG, i, explored, leaders, i, f);
            cnt++;
        }
    }

    delete []explored;

    return leaders;
}

void printGraph(const vector<vector<int>>& G)
{
    for (int i = 0; i < G.size(); ++i)
    {
        cout << i << " > ";
        for (int j = 0; j < G[i].size(); ++j)
            cout << G[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> G;
    vector<vector<int>> Grev;
    get_input("test1.txt", 6, G, Grev);
    printGraph(G);
    cout << endl;
    printGraph(Grev);

    int* f = new int[Grev.size()];

    dfsLoop1(Grev, f);

    cout << "f = ";
    for (int i = 0; i < Grev.size(); ++i)
        cout << f[i] << " ";
    cout << endl;

    vector<vector<int>> newG(G.size());
    for (int i = 0; i < newG.size(); ++i)
    {
        vector<int> adj;
        for (int j = 0; j < G[i].size(); ++j)
            adj.push_back(f[G[i][j]]);
        newG[f[i]] = adj;
    }

    printGraph(newG);

    int cnt = 0;
    auto leaders = dfsLoop2(G, f, cnt);

    for (const auto& i : leaders)
        cout << i << " ";
    cout << endl;

    cout << "SCCs = " << cnt << endl;

    delete []f;
    return 0;
}
