#include <bits/stdc++.h>

using namespace std;

#define taskname "E"

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

const int INF = 1e9 + 7;

struct SegmentTree
{
    int size;
    vector<int> tree;

    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        tree.assign(2 * size, INF);
    }

    void update(int i, int h)
    {
        update(1, 0, size - 1, i, h);
    }

    void update(int x, int lx, int rx, int i, int h)
    {
        if (rx == lx)
        {
            tree[x] = h;
            return;
        }

        int m = (lx + rx) / 2;

        if (i <= m)
            update(2 * x, lx, m, i, h);
        else
            update(2 * x + 1, m + 1, rx, i, h);

        tree[x] = min(tree[2 * x], tree[2 * x + 1]);
    }

    int get(int l, int r, int p)
    {
        return get(1, 0, size - 1, l, r, p);
    }

    int get(int x, int lx, int rx, int l, int r, int p)
    {
        if (lx > r || rx < l)
            return 0;

        if (tree[x] > p)
            return 0;
        
        if (rx == lx)
        {
            tree[x] = INF;
            return 1;
        }

        int m = (lx + rx) / 2;

        int get1 = get(2 * x, lx, m, l, r, p);
        int get2 = get(2 * x + 1, m + 1, rx, l, r, p);

        tree[x] = min(tree[2 * x], tree[2 * x + 1]);

        return get1 + get2;
    }
};

void Solve()
{
    int n, m;
    cin >> n >> m;

    SegmentTree st;
    st.init(n);

    while (m--)
    {
        int op;
        cin >> op;

        if (op == 1)
        {
            int i, v;
            cin >> i >> v;
            st.update(i, v);
        }
        else
        {
            int l, r, p;
            cin >> l >> r >> p;
            ce1(st.get(l, r - 1, p));
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