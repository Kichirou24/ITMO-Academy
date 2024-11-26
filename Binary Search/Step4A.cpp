#include <bits/stdc++.h>

using namespace std;

pair<int, int> solve(const vector<int> &a, const int d)
{
    int n = a.size();

    auto Check = [&a, n, d](double avg, bool check) -> pair<bool, pair<int, int>>
    {
        vector<double> Sum(n + 1), Min(n + 1);

        Sum[0] = 0;
        Min[0] = 0;

        for (int i = 0; i < n; i++)
        {
            Sum[i + 1] = Sum[i] + (a[i] - avg);
            Min[i + 1] = min(Min[i], Sum[i + 1]);
        }

        for (int j = n - 1; j >= d - 1; j--)
        {
            if (Min[j + 1 - d] <= Sum[j + 1])
            {
                int i = j + 1 - d;
                if (check)
                {
                    while(Sum[i] > Sum[j + 1]) i--;
                }
                return {true, {i, j}};
            }
        }
        return {false, {0, 0}};
    };

    double lo = 0.0, hi = 101.0;

    for (int i = 0; i < 25; i++)
    {
        auto m = lo + (hi - lo) / 2;
        if (Check(m, false).first) lo = m;
        else hi = m;
    }
    return Check(lo, true).second;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, d;
    cin >> n >> d;

    vector<int> a(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];

    auto ans = solve(a, d);
    cout << ans.first + 1 << " " << ans.second + 1<< endl;

    return 0;
}