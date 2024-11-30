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

struct SegmentTree
{
    int size;

    struct Node
    {
        int sum;
        int cnt;
    };

    Node calc(Node a, Node b)
    {
        if (a.cnt % 2 == 0)
            return {a.sum + b.sum, a.cnt + b.cnt};
        else
            return {a.sum - b.sum, a.cnt + b.cnt};
    }

    vector<Node> tree;

    void init(vector<int> &a)
    {
        size = 1;
        while (size < a.size())
            size *= 2;
        tree.assign(2 * size, {0, 0});
        build(a, 0, 0, size);
    }

    void build(vector<int> &a, int x, int lx, int rx)
    {
        if (rx == lx + 1)
        {
            if (lx < a.size())
                tree[x] = {a[lx], 1};
            return;
        }

        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);

        tree[x] = calc(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void update(int x, int lx, int rx, int id, int v)
    {
        if (rx == lx + 1)
        {
            tree[x] = {v, 1};
            return;
        }

        int m = (lx + rx) / 2;
        if (id < m)
            update(2 * x + 1, lx, m, id, v);
        else
            update(2 * x + 2, m, rx, id, v);

        tree[x] = calc(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void update(int id, int v)
    {
        return update(0, 0, size, id, v);
    }

    Node get(int x, int lx, int rx, int l, int r)
    {
        if (lx >= r || rx <= l)
            return {0, 0};

        if (lx >= l && rx <= r)
            return tree[x];

        int m = (lx + rx) / 2;
        Node get1 = get(2 * x + 1, lx, m, l, r);
        Node get2 = get(2 * x + 2, m, rx, l, r);

        return calc(get1, get2);
    }

    int get(int l, int r)
    {
        return get(0, 0, size, l, r).sum;
    }

    void show()
    {
        for (auto x : tree)
            cout << x.sum << " ";
        cout << endl;
    }
};

void Solve()
{
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &x : a)
        cin >> x;

    int m;
    cin >> m;

    SegmentTree st;
    st.init(a);

    // st.show();

    while (m--)
    {
        int op;
        cin >> op;

        if (op == 0)
        {
            int i, j;
            cin >> i >> j;

            st.update(i - 1, j);
        }
        else
        {
            int l, r;
            cin >> l >> r;

            ce1(st.get(l - 1, r))
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