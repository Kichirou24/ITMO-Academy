#include <bits/stdc++.h>

using namespace std;

long long solve(const long long n,const long long k)
{
    auto Check = [n, k] (long long x)
    {
        long long cnt = 0;
        for (long long i = 1; i <= n; i++)
        {
            if (x > 1)
            {
                cnt += min((x - 1) / i, n);
                if (cnt >= k) return false;
            }
        }
        return true;
    };

    long long lo = 1, hi = n * n + 1;
    while (lo + 1 < hi)
    {
        long long m = lo + (hi - lo) / 2;
        if (Check(m)) lo = m;
        else hi = m;
    }
    return lo;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long n, k;
    cin >> n >> k;

    cout << solve(n, k);

    return 0;
}