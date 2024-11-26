#include <bits/stdc++.h>

using namespace std;

int main()
{
    double C;

    cin >> C;

    auto check = [C](double t)
    {
        auto x = t * t;
        return x * x + t >= C;
    };

    double l = 0.5, r = C;

    const int n = 100;
    for (auto i = 0; i < n; i++)
    {
        auto m = l + (r - l) / 2;
        if (check(m))
            r = m;
        else
            l = m;
    }
    cout << setprecision(20) << l * l << endl;

    return 0;
}