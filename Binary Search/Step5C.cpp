#include <bits/stdc++.h>

using namespace std;

int solve(vector<int> &a, vector<int> &b, const int k)
{
    sort(b.begin(), b.end());

    auto Check = [&a, &b, k](int x)
    {
        int cnt = 0;
        for (const auto &ai : a)
        {
            if (ai < x)
            {
                cnt += (lower_bound(b.begin(), b.end(), x - ai) - b.begin());
                if (cnt >= k)
                {
                    return false;
                }
            }
        }
        return true;
    };

    int lo = 1, hi = 2e9 + 1;
    while (lo + 1 < hi)
    {
        auto m = lo + (hi - lo) / 2;
        if (Check(m))
        {
            lo = m;
        }
        else
        {
            hi = m;
        }
    }
    return lo;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<int> a(n), b(n);

    for (auto i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (auto i = 0; i < n; i++)
    {
        cin >> b[i];
    }

    cout << solve(a, b, k) << endl;
    return 0;
}