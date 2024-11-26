#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;

    cin >> n >> k;

    vector<int> a(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];

    auto check = [&a, k](long long d)
    {
        int cnt = 0, last = -1e9;

        for (const auto pos : a)
        {
            if (pos - last >= d)
            {
                cnt++;
                last = pos;
            }
            if (cnt >= k) return true;
        }

        return false;
    };

    long long lo = 1, hi = 1e9;

    while (lo + 1 < hi)
    {
        auto m = lo + (hi - lo) / 2;
        if (check(m))
            lo = m;
        else
            hi = m;
    }

    cout << lo << endl;

    return 0;
}