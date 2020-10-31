#include <iostream>
#include <vector>

using namespace std;
vector< vector<int> > mult(vector< vector <int> > a, vector< vector <int> > b) {
    vector< vector <int> > c(a.size());
    for (int i = 0; i < a.size(); ++i) 
        for (int j = 0; j < b[0].size(); ++j) {
            c[i].push_back(0);
            for (int k = 0; k < b.size(); ++k)
                c[i][j] += a[i][k] * b[k][j];
        }
    return c;
}
vector< vector<int> > power(vector< vector <int> > a, int n) {
    vector< vector <int> > c = a;
    while (n != 0) {
        if (n % 2 != 0)
        {
            c = mult(c, a);
            --n;
        }
        else {
            a = mult(a, a);
            n /= 2;
        }
    }
    return c;
}
int main()
{
    int n, m, k, i, j;
    vector< vector<int> > a(2), ed(1);
    a[0].push_back(0);
    a[0].push_back(1);
    a[1].push_back(1);
    a[1].push_back(1);
    ed[0].push_back(0);
    ed[0].push_back(1);
    cin >> n;
    a = power(a, n);
    ed = mult(ed, a);
    cout << ed[0][0];
}
