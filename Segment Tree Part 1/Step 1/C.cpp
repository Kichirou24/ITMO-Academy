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

const int MAXN = 1e5;
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
    struct Node
    {
        int val, cnt;
        Node()
        {
            val = LLONG_MAX;
            cnt = 0;
        };

        Node(int val, int cnt)
        {
            this->val = val;
            this->cnt = cnt;
        };
    };

    int size;
    vector<Node> tree;

    SegmentTree(int n)
    {
        size = n;
        tree.resize(4 * n);
    }

    Node merge(Node a, Node b)
    {
        if (a.val < b.val)
            return a;
        if (a.val > b.val)
            return b;
        return Node(a.val, a.cnt + b.cnt);
    }

    void build(vector<int> &a, int v, int lv, int rv)
    {
        if (lv == rv)
            tree[v] = Node(a[lv], 1);
        else
        {
            int tm = (lv + rv) / 2;

            build(a, v * 2, lv, tm);
            build(a, v * 2 + 1, tm + 1, rv);

            tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    void update(int v, int lv, int rv, int pos, int newVal)
    {
        if (lv == rv)
            tree[v] = Node(newVal, 1);
        else
        {
            int tm = (lv + rv) / 2;
            if (pos <= tm)
                update(v * 2, lv, tm, pos, newVal);
            else
                update(v * 2 + 1, tm + 1, rv, pos, newVal);
            tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    Node query(int v, int lv, int rv, int l, int r)
    {
        if (l > r)
            return Node();
        if (l == lv && r == rv)
            return tree[v];
        int tm = (lv + rv) / 2;
        return merge(query(v * 2, lv, tm, l, min(r, tm)),
                     query(v * 2 + 1, tm + 1, rv, max(l, tm + 1), r));
    }

    void build(vector<int> &a)
    {
        build(a, 1, 0, size - 1);
    }

    void update(int pos, int newVal)
    {
        update(1, 0, size - 1, pos, newVal);
    }

    Node query(int l, int r)
    {
        return query(1, 0, size - 1, l, r);
    }
};

void Solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (auto &i : a)
        cin >> i;

    SegmentTree segTree(n);
    segTree.build(a);

    for (int i = 0; i < m; ++i)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int i, v;
            cin >> i >> v;
            segTree.update(i, v);
        }
        else if (op == 2)
        {
            int l, r;
            cin >> l >> r;
            SegmentTree::Node res = segTree.query(l, r - 1);
            ce2(res.val, res.cnt)
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
        cerr << "lvE\n";
    return 0;
}