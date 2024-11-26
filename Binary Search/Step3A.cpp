#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    vector<int> x(n), v(n);

    for (int i = 0; i < n; i++)
        cin >> x[i] >> v[i];

    const auto len = x.size();
    auto check = [&x, &v, len](double time)
    {
        double left = -1e9, right = 1e9;
        for (auto i = 0; i < len; i++)
        {
            auto l = x[i] - time * v[i], r = x[i] + time * v[i];

            if (l > right || r < left)
                return false;

            left = max(left, l);
            right = min(right, r);
        }
        return true;
    };

    double lo = -0.1, hi = 1e9;
    const auto mx = 100;

    for (int i = 0; i < mx; i++)
    {
        auto m = lo + (hi - lo) / 2;
        if (check(m))
            hi = m;
        else
            lo = m;
    }

    cout << fixed << setprecision(20) << hi << endl;

    return 0;
}