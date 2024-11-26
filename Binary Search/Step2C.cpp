#include <bits/stdc++.h>

using namespace std;

long long n, x, y;

bool check(double z)
{
    if (z >= min(x, y))
    {
        z -= min(x, y);
        return floor(z / x) + floor(z / y) >= n - 1;
    }
    else
        return 0;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> x >> y;

    long long l = 0;
    long long r = 2e9;

    while (r > l + 1)
    {
        long long m = (r + l) / 2;

        if (check(m))
            r = m;
        else
            l = m;
    }

    cout << r << endl;

    return 0;
}