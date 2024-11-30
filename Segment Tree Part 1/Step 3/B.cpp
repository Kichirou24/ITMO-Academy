#include <bits/stdc++.h>

using namespace std;

#define taskname "B"

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

class SegmentTree
{
    int size;
    vector<int> tree;

public:
    void build(vector<int> &a)
    {
        size = 1;
        while (size < a.size())
            size *= 2;
        tree.assign(2 * size, 0);
        build(a, 1, 0, size - 1);
    }

    void build(vector<int> &a, int x, int lx, int rx)
    {
        if (rx == lx)
        {
            if (lx < a.size())
                tree[x] = a[lx];
        }
        else
        {
            int m = (lx + rx) / 2;
            build(a, 2 * x, lx, m);
            build(a, 2 * x + 1, m + 1, rx);

            tree[x] = tree[2 * x] + tree[2 * x + 1];
        }
    }

    void update(int x, int lx, int rx, int id, int v)
    {
        if (rx == lx)
            tree[x] = v;
        else
        {
            int m = (lx + rx) / 2;

            if (id <= m)
                update(2 * x, lx, m, id, v);
            else
                update(2 * x + 1, m + 1, rx, id, v);
            
            tree[x] = tree[2 * x] + tree[2 * x + 1];
        }
    }

    void update(int id, int v)
    {
        update(1, 0, size - 1, id, v);
    }

    int get(int x, int lx, int rx, int i)
    {
        if (tree[x] <= i)
            return -1;
        if (rx == lx)
            return lx;
        
        int m = (lx + rx) / 2;
        int res = get(2 * x, lx, m, i);
        if (res == -1)
            res = get(2 * x + 1, m + 1, rx, i - tree[2 * x]);
        
        return res;
    }

    int get(int i)
    {
        return get(1, 0, size - 1, i);
    }
};

void Solve()
{
    int n;
    cin >> n;

    vector<int> a(n), b(n, 1);
    for (auto &x : a)
        cin >> x;

    SegmentTree st;
    st.build(b);

    int k;
    int sz = n;

    vector<int> res(n);
    for (int i = n - 1; i >= 0; --i)
    {
        cin >> k;

        int r = st.get(sz - a[i] - 1);
        st.update(r, 0);
        --sz;
        res[i] = r + 1;
    }

    for (auto x : res)
        c1(x)
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