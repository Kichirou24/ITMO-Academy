#include <bits/stdc++.h>
using namespace std;

int main()
{
    int m, n;

    while (cin >> m >> n)
    {
        vector<int> t(n), z(n), y(n);

        for (int i = 0; i < n; i++)
        {
            cin >> t[i] >> z[i] >> y[i];
        }

        auto ballonnums = [&t, &z, &y](int i, int time)
        {
            auto temp = t[i] * z[i] + y[i];
            return time / temp * z[i] + min((time % temp) / t[i], z[i]);
        };

        auto check = [m, n, &ballonnums](int time)
        {
            int temp = 0;
            for (int i = 0; i < n; i++)
            {
                temp += ballonnums(i, time);
                if (temp >= m)
                {
                    return true;
                }
            }
            return false;
        };

        int l = -1, r = m * 200;

        while (l + 1 < r)
        {
            auto m = l + (r - l) / 2;

            if (check(m))
                r = m;
            else
                l = m;
        }

        cout << r << endl;
        auto count = m;

        for (int i = 0; i < n; i++)
        {
            auto num = ballonnums(i, r);

            if (num > count)
            {
                num = count;
            }
            count -= num;
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}
