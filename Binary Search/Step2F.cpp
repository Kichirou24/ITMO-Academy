#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string p, t;

    cin >> p >> t;

    const int n = p.size();

    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    auto check = [n, &p, &t, &a](int cnt)
    {
        string newp(p);
        for (auto i = 0; i < cnt; i++)
        {
            newp[a[i] - 1] = '*';
        }

        int temp = 0;

        for (const auto &c : t)
        {
            while (temp < n && newp[temp] != c)
            {
                temp++;
            }
            if (temp >= n)
                return false;
            temp++;
        }
        return true;
    };

    int l = 0, r = n - t.size() + 1;

    while (l + 1 < r)
    {
        auto m = l + (r - l) / 2;
        if (check(m))
            l = m;
        else
            r = m;
    }

    cout << l << endl;

    return 0;
}
