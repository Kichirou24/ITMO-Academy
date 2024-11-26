#include <bits/stdc++.h>

using namespace std;

vector<int> solve(const vector<vector<pair<int, int>>> &A, const int n)
{
    auto Check = [&A, n](double avg, bool check) -> pair<bool, vector<int>>
    {
        vector<double> dp(n + 1, 1126);
        vector<int> p(n + 1, -1);
        dp[1] = 0.0;

        for (auto i = 1; i <= n; i++)
        {
            if (i != 1 && p[i] == -1)
                continue;

            for (const auto &x : A[i])
            {
                if (dp[i] + x.second - avg < dp[x.first])
                {
                    dp[x.first] = dp[i] + x.second - avg;
                    p[x.first] = i;
                }
            }

            if (dp[n] <= 0)
                break;
        }

        vector<int> trace;
        if (check && dp[n] <= 0)
        {
            trace.push_back(n);
            while (p[trace[trace.size() - 1]] != -1)
                trace.push_back(p[trace[trace.size() - 1]]);
            reverse(trace.begin(), trace.end());
        }

        return {dp[n] <= 0, trace};
    };

    double lo = -0.1, hi = 100.1;

    for (auto i = 0; i < 30; i++)
    {
        auto m = lo + (hi - lo) / 2;
        if (Check(m, false).first)
            hi = m;
        else
            lo = m;
    }
    return Check(hi, true).second;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    
    vector<vector<pair<int, int>>> A(n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        A[a].push_back({b, c});
    }

    auto trace = solve(A, n);
    cout << trace.size() - 1 << endl;
    for (const auto &x : trace)
    {
        cout << x << " ";
    }
    return 0;
}