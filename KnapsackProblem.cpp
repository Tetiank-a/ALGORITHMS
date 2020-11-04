#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
int main()
{
    int n, m, k = 0, x, y, w;
    cin >> n >> w;
    vector< pair<int, int> > a(n);
    vector< vector<int> > d(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i].first >> a[i].second;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= w; ++j)
            d[i].push_back(0);
    for (int i = 0; i <= w; ++i)
        if (a[0].first <= i) d[0][i] = a[0].second;
    for (int i = 1; i < n; ++i)
        for (int j = 1; j <= w; ++j) {
            d[i][j] = max(d[i - 1][j], d[i][j - 1]);
            if (a[i].first <= j)
                d[i][j] = max(d[i - 1][j - a[i].first] + a[i].second, d[i][j]);
        }
    cout << d[n - 1][w] << endl;
    int res = d[n - 1][w];
    x = n - 1;
    y = w;
    while (res > 0) {
        if (res == a[x].second) {
            cout << x << " ";
            break;
        }
        if (res == 0) break;
        if (d[x][y] == d[x - 1][y])
            x--;
        else 
        if (d[x][y] == d[x][y - 1])
            y--;
        else 
        if (d[x][y] == d[x - 1][y - a[x].first] + a[x].second) {
            res -= a[x].second;
            cout << x << " ";
            y -= a[x].first;
            x--;
        }
    }
}
