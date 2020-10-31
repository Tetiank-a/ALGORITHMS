#include <iostream>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

vector<bool> used;
void dfs(vector< vector<int> > a, int v) {
    used[v] = 1;
    for (int i = 0; i < a[v].size(); ++i) {
        if (used[a[v][i]] == 0)
            dfs(a, a[v][i]);
    }
}

int main()
{
    int n, m, k = 0, x, y;
    cin >> n >> m;
    vector< vector <int> > a(n);
    for (int i = 0; i < m; ++i)
    {
        cin >> x >> y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    for (int i = 0; i < n; ++i)
        used.push_back(0);
    for (int i = 0; i < n; ++i)
    {
        if (used[i] == 0) {
            dfs(a, i);
            k++;
        }
    }
    cout << k;
}
