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
    
    vector<int> p_new(n);
    vector<int> pos(n);

    pos[0] = 0;

    for (int i = 1; i < n; ++i)
        pos[i] = pos[i - 1] + cnt[i - 1];

    for (auto x : p)
    {
        int id = c[x];
        p_new[pos[id]] = x;
        ++pos[id];
    }

    p = p_new;
}

void Solve()
{
    string st;
    cin >> st;
    st += "$";

    int n = st.size();

    vector<pair<char, int>> a(n);
    vector<int> p(n), c(n);
    for (int i = 0; i < n; ++i)
        a[i] = {st[i], i};

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
            pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};

            c_new[p[i]] = c_new[p[i - 1]];
            if (prev != cur)
                ++c_new[p[i]];
        }
        c = c_new;
        ++k;
    }

    for (int i = 0; i < n; ++i)
        c1(p[i])
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