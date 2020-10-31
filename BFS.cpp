#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <cmath>

using namespace std;
int INF = 10e6+7;
vector<int> dist, p;
void bfs(vector< vector<int> > a, int v) {
    for (int i = 0; i < a.size(); ++i) {
        dist.push_back(-1);
        p.push_back(-1);
    }
    dist[v] = 0;
    queue<int> q;
    vector<bool> used(a.size(), 0);
    q.push(v);
    int len = 0;
    used[v] = 1;
    while (!q.empty()) {
        v = q.front();
        q.pop();
        for (int i = 0; i < a[v].size(); ++i) {
            int to = a[v][i];
            if (used[to] == 0) {
                q.push(to);
                dist[to] = dist[v] + 1;
                used[to] = 1;
                p[to] = v;
            }
        }
    }
}

int main()
{
    int n, m, k, x, y;
    cin >> n >> m;
    vector< vector<int> > a(n);
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        a[x].push_back(y);
    }
    bfs(a, 0);
    for (int i = 0; i < n; ++i)
        cout << dist[i] << " ";
    cout << '\n';
    x = n - 1; // path to vertex number (n - 1)
    while (x != -1) {
        cout << x << " ";
        x = p[x];
    }
}
