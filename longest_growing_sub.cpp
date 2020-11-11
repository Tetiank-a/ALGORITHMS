#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <algorithm>
#include <set>

std::vector<int> p;
std::vector< std::pair<int, int> > dp;

int max_pos(std::vector<int> a) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        if (dp.size() == 0 || a[i] > dp[dp.size() - 1].first) {
            dp.push_back({a[i], i});
            if (dp.size() == 1)
                p[i] = -1;
            else
                p[i] = dp[dp.size() - 2].second;
        }
        else {
            std::pair<int, int> fin = { a[i] - 1, i };
            int x = std::upper_bound(dp.begin(), dp.end(), fin) - dp.begin();
            dp[x] = {a[i] , i};
            if (x == 0)
                p[i] = -1;
            else
                p[i] = dp[x - 1].second;
        }
    }
    return dp.size();
}

int main()
{
    int64_t n, x, k = 0, y;
    std::cin >> n;
    std::vector <int> a;
    p = std::vector<int>(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> x;
        a.push_back(x);
    }
    std::cout << max_pos(a) << '\n';

    k = dp[dp.size() - 1].second;
    std::vector<int> ans;
    while (k != -1) {
        ans.push_back(a[k]);
        k = p[k];
    }
    for (int i = ans.size() - 1; i >= 0; --i)
        std::cout << ans[i] << " ";
}
