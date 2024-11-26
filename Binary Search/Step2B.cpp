#include <bits/stdc++.h>

using namespace std;

int n, k;
vector<double> a(n);

bool check(double x)
{
    int s = 0;
    for (int i = 0; i < n; i++)
    {
        s += floor(a[i] / x);
    }

    return s >= k;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> k;
    a.resize(n);
    
    for (int i = 0; i < n; i++) cin >> a[i];

    double l = 0, r = 1e8;

    for (int i = 0; i < 100; i++)
    {
        double m = (l + r) / 2;
        if (check(m))
        {
            l = m;
        }
        else 
        {
            r = m;
        }
    }

    cout << setprecision(20) << l << endl;

    return 0;
}
