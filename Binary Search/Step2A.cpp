#include <iostream>

using namespace std;

long long w, h, n;

bool check(long long x)
{
    return ((x / w )* (x / h) >= n);
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> w >> h >> n;

    long long l = 0, r = 1;

    while (!check(r))
        r *= 2;

    while (r > l + 1)
    {
        long long m = (l + r) / 2;
        if (check(m))
            r = m;
        else
            l = m;
    }

    cout << r << endl;

    return 0;
}