#include <bits/stdc++.h>

using namespace std;

#define taskname "A"

int nTest = 1;

#define pb(x, y) x.push_back(y);
#define fi first
#define se second
#define int long long
#define c1(x) cout << x << " ";
#define c2(x, y) cout << x << " " << y << " ";
#define ce1(x) cout << x << endl;
#define ce2(x, y) cout << x << " " << y << endl;

const int MAXN = 2e6 + 10;
const int MOD = 1e9 + 7;

typedef pair<int, int> PII;

void Input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if (fopen(taskname ".inp", "r"))
    {
        freopen(taskname ".inp", "r", stdin);
        freopen(taskname ".out", "w", stdout);
    }
    // cin >> nTest;
}

void cntSort(vector<int> &p, vector<int> &c)
{
    int n = p.size();

    vector<int> cnt(n);

    for (auto x : c)
        ++cnt[x];

    vector<int> pos(n);

    pos[0] = 0;

    for (int i = 1; i < n; ++i)
        pos[i] = pos[i - 1] + cnt[i - 1];

    vector<int> p_new(n);
    for (auto x : p)
    {
        int i = c[x];
        p_new[pos[i]] = x;
        ++pos[i];
    }

    p = p_new;
}

void Solve()
{
    string s;
    cin >> s;

    s += "$";

    int n = s.size();

    vector<int> p(n), c(n);
    {
        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; ++i)
            a[i] = {s[i], i};

        sort(a.begin(), a.end());

        for (int i = 0; i < n; ++i)
            p[i] = a[i].se;

        c[p[0]] = 0;
        for (int i = 1; i < n; ++i)
        {
            c[p[i]] = c[p[i - 1]];
            if (a[i].fi != a[i - 1].fi)
                ++c[p[i]];
        }
    }

    int k = 0;

    while ((1 << k) < n)
    {
        for (int i = 0; i < n; ++i)
            p[i] = (p[i] - (1 << k) + n) % n;

        cntSort(p, c);

        vector<int> c_new(n);
        c_new[p[0]] = 0;

        for (int i = 1; i < n; ++i)
        {
            PII prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            PII now = {c[p[i]], c[(p[i] + (1 << k)) % n]};

            c_new[p[i]] = c_new[p[i - 1]];
            if (prev != now)
                ++c_new[p[i]];
        }

        c = c_new;
        ++k;
    }

    k = 0;
    vector<int> lcp(n);

    for (int i = 0; i < n - 1; ++i)
    {
        int ci = c[i];
        int j = p[ci - 1];
        while (s[i + k] == s[j + k])
            ++k;
        
        lcp[ci] = k;
        k = max(k - 1, 0LL);
    }

    int res = 0;
    for (int i = 1; i < n; ++i)
        res += n - 1 - p[i] - lcp[i];

    ce1(res)
}

signed main()
{
    clock_t begin = clock();
    Input();
    while (nTest--)
        Solve();

    cerr << "Time: " << (clock() - begin + 1.0) / CLOCKS_PER_SEC << "s\n";
    if (((clock() - begin + 1.0) / CLOCKS_PER_SEC) > 2.0)
        cerr << "TLE\n";
    return 0;
}