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

    const auto len = a.size();
    auto check = [&a, k, len](long long sum)
    {
        int cnt = 1;
        long long tempsum = 0;
        for (const auto x : a)
        {
            if (tempsum + x > sum)
            {
                cnt++;
                tempsum = 0;
            }
            if (x > sum || cnt > k) return false; 
            tempsum += x;
        }
        return true;
    };

    long long lo = 0, hi = len * 1e9;

    while (lo + 1 < hi)
    {
        auto m = lo + (hi - lo) / 2;
        if (check(m))
            hi = m;
        else
            lo = m;
    }

    cout << hi << endl;

    return 0;
}