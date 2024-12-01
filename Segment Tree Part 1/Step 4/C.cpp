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

struct SegmentTree{
    struct Node {
        int f[41];
        int cnt;
    };

    int size;
    vector<Node> tree;
    Node z;

    Node add(Node a, Node b)
    {
        Node res;
        memset(res.f, 0, sizeof(res.f));

        for (int i = 0; i < 41; ++i)
            res.f[i] = a.f[i] + b.f[i];
        int cnt = a.cnt + b.cnt;

        for (int i = 0; i < 41; ++i)
            for (int j = i + 1; j < 41; ++j)
                cnt += b.f[i] * a.f[j];

        res.cnt = cnt;
        return res;
    }

    void init(vector<int> &a)
    {
        memset(z.f, 0, sizeof(z.f));
        z.cnt = 0;

        size = 1;
        while (size < a.size())
            size *= 2;
        
        tree.assign(2 * size, z);
        build(a, 1, 0, size - 1);
    }

    void build(vector<int> &a, int x, int lx, int rx)
    {
        if (rx == lx)
        {
            if (lx < a.size())
            {
                memset(tree[x].f, 0, sizeof(tree[x].f));
                ++tree[x].f[a[lx]];
                tree[x].cnt = 0;
            }
            return;
        }

        int m = (lx + rx) / 2;
        build(a, 2 * x, lx, m);
        build(a, 2 * x + 1, m + 1, rx);

        tree[x] = add(tree[2 * x], tree[2 * x + 1]);
    }

    void update(int x, int lx, int rx, int id, int v)
    {
        if (rx == lx)
        {
            memset(tree[x].f, 0, sizeof(tree[x].f));
            ++tree[x].f[v];
            tree[x].cnt = 0;
            return;
        }

        int m = (lx + rx) / 2;
        if (id <= m)
            update(2 * x, lx, m, id, v);
        else
            update(2 * x + 1, m + 1, rx, id, v);

        tree[x] = add(tree[2 * x], tree[2 * x + 1]);
    }

    void update(int id, int v)
    {
        update(1, 0, size - 1, id, v);
    }

    Node get(int x, int lx, int rx, int l, int r)
    {
        if (lx > r || rx < l)
            return z;

        if (lx >= l && rx <= r)
            return tree[x];
        
        int m = (lx + rx) / 2;
        Node get1 = get(2 * x, lx, m, l, r);
        Node get2 = get(2 * x + 1, m + 1, rx, l, r);

        return add(get1, get2);
    }

    int get(int id, int v)
    {
        return get(1, 0, size - 1, id, v).cnt;
    }
};

void Solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (auto &x : a)
        cin >> x;

    SegmentTree st;
    st.init(a);

    while (m--)
    {
        int op;
        cin >> op;

        if (op == 1)
        {
            int l, r;
            cin >> l >> r;

            ce1(st.get(l - 1, r - 1));
        }
        else
        {
            int x, y;
            cin >> x >> y;

            st.update(x - 1, y);
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