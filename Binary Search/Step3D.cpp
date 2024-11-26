#include <bits/stdc++.h>

using namespace std;

vector<int> find(const vector<vector<pair<int, int>>> &A, int d, int Min, int Max)
{
    auto len = A.size() - 1;

    std::function<bool(int, vector<int> &, set<int> &, map<int, int> &)> dfs;
    dfs = [&A, len, d, &dfs](int limit, vector<int> &trace, set<int> &seen, map<int, int> &save) -> bool
    {
        auto i = trace[trace.size() - 1];

        if (save.find(i) != save.end() && save[i] <= trace.size())
            return false;

        save[i] = trace.size();

        if (i == len)
            return true;

        if (trace.size() >= d + 1)
            return false;

        for (const auto &t : A[i])
        {
            if (t.second > limit || seen.find(t.first) != seen.end())
                continue;

            trace.push_back(t.first);
            seen.insert(t.first);

            if (dfs(limit, trace, seen, save))
                return true;

            seen.erase(t.first);
            trace.pop_back();
        }
        return false;
    };

    auto check = [&dfs](int limit)
    {
        vector<int> trace = {1};
        set<int> seen = {1};
        map<int, int> save;

        return dfs(limit, trace, seen, save);
    };

    if (!check(Max))
    {
        return vector<int>();
    }

    auto lo = Min - 1, hi = Max;

    while (lo + 1 < hi)
    {
        auto m = lo + (hi - lo) / 2;

        if (check(m))
            hi = m;
        else
            lo = m;
    }

    vector<int> trace = {1};
    set<int> seen = {1};
    map<int, int> save;
    dfs(hi, trace, seen, save);
    return trace;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, d;
    cin >> n >> m >> d;

    vector<vector<pair<int, int>>> A(n + 1);

    int Min = 1e9, Max = 0;

    for (int i = 0; i < m; i++)
    {
        int a, b, c;

        cin >> a >> b >> c;

        A[a].push_back({b, c});
        Min = min(Min, c);
        Max = max(Max, c);
    }

    auto ans = find(A, d, Min, Max);

    if (ans.size() == 0) cout << -1 << endl;
    else
    {
        cout << ans.size() - 1 << endl;
        for (const auto x : ans) cout << x << " ";
        cout << endl;
    }

    return 0;
}