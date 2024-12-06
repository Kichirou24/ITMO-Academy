#include <bits/stdc++.h>

using namespace std;

#define taskname "B"

int nTest = 1;

#define pb(x, y) x.push_back(y);
#define fi first
#define se second
// #define int long long
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

int get(int x, vector<int> &p)
{
    if (x != p[x])
        p[x] = get(p[x], p);

    return p[x];
}

void Solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> p(n + 1), r(n + 1), mi(n + 1), MA(n + 1), s(n + 1);

    for (int i = 1; i <= n; i++)
    {
        p[i] = i;
        r[i] = 1;
        s[i] = 1;
        mi[i] = i;
        MA[i] = i;
    }

    while (m--)
    {
        string op;
        cin >> op;
        if (op == "union")
        {
            int u, v;
            cin >> u >> v;

            int x = get(u, p);
            int y = get(v, p);
            if (x == y)
                continue;

            if (r[x] == r[y])
            {
                ++r[x];
                p[y] = x;
                s[x] += s[y];
                mi[x] = min(mi[x], mi[y]);
                MA[x] = max(MA[x], MA[y]);
            }
            else if (r[x] > r[y])
            {
                p[y] = x;
                s[x] += s[y];
                mi[x] = min(mi[x], mi[y]);
                MA[x] = max(MA[x], MA[y]);
            }
            else
            {
                p[x] = y;
                s[y] += s[x];
                mi[y] = min(mi[x], mi[y]);
                MA[y] = max(MA[x], MA[y]);
            }
        }
        else
        {
            int v;
            cin >> v;
            int x = get(v, p);

            cout << mi[x] << " " << MA[x] << " " << s[x] << endl;
        }
    }
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