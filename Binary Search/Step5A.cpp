#include <bits/stdc++.h>

using namespace std;

int solve(const vector<pair<int, int>> &A, const int k)
{
    auto Check = [&A, k] (long long x)
    {
        long long cnt = 0;
        for (const auto &a : A)
        {
            if (x > a.first) cnt += min(x - a.first, (long long)a.second - a.first + 1);
            if (cnt > k) return false;
        }
        return true;
    };

    long long lo = -2e9, hi = 2e9 + 1;
    while (lo + 1 < hi)
    {
        auto m = lo + (hi - lo) / 2;
        if (Check(m)) lo = m;
        else hi = m;
    }
    return lo;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> A(n);

    for (int i = 0; i < n; i++) cin >> A[i].first >> A[i].second;

    cout << solve(A, k) << endl;

    return 0;
}