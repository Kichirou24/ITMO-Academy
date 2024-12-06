#include <bits/stdc++.h>

using namespace std;

#define taskname "C"

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

int get(int x, vector<int> &p)
{
    if (x != p[x])
        p[x] = get(p[x], p);
    
    return p[x];
}

int getRes(int x, vector<int> &p, vector<int> &res)
{
    int ans = res[x];
    if (x != p[x])
    {
        x = p[x];
        ans += res[x];
    }
    
    return ans;
}

void Solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> r(n + 1), p(n + 1), res(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        r[i] = 1;
        p[i] = i;
        res[i] = 0;
    }

    while (m--)
    {
        string op;
        cin >> op;

        if (op == "add")
        {
            int u, v;
            cin >> u >> v;

            int x = get(u, p);
            
            res[x] += v;

        } else if (op == "join")
        {
            int u, v;
            cin >> u >> v;

            int x = get(u, p);
            int y = get(v, p);

            if (x == y)
                continue;

            if (r[x] == r[y])
                ++r[x];

            if (r[x] > r[y])
            {
                p[y] = x;
                res[y] -= res[x];
            }
            else
            {
                p[x] = y;
                res[x] -= res[y];
            }
        }
        else
        {
            int v;
            cin >> v;

            ce1(getRes(v, p, res))
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