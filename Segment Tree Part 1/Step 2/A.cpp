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
    struct Node
    {
        int sum, maxSum, sum1, sum2;
        Node()
        {
            sum = maxSum = sum1 = sum2 = 0;
        }
        Node(int val)
        {
            sum = maxSum = sum1 = sum2 = val;
        }
    };

    int n;
    vector<Node> tree;

    SegmentTree(const vector<int> &a)
    {
        n = a.size();
        tree.resize(4 * n);
        build(a, 0, 0, n - 1);
    }

    void build(const vector<int> &a, int node, int l, int r)
    {
        if (l == r)
            tree[node] = Node(a[l]);
        else
        {
            int m = (l + r) / 2;
            build(a, 2 * node + 1, l, m);
            build(a, 2 * node + 2, m + 1, r);

            tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    Node merge(const Node &l, const Node &r)
    {
        Node res;

        res.sum = l.sum + r.sum;

        res.sum1 = max(l.sum1, l.sum + r.sum1);
        res.sum2 = max(r.sum2, r.sum + l.sum2);
        res.maxSum = max({l.maxSum, r.maxSum, l.sum2 + r.sum1});

        return res;
    }

    void update(int idx, int val, int node, int l, int r)
    {
        if (l == r)
            tree[node] = Node(val);
        else
        {
            int m = (l + r) / 2;
            if (idx <= m)
                update(idx, val, 2 * node + 1, l, m);
            else
                update(idx, val, 2 * node + 2, m + 1, r);

            tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    void update(int idx, int val)
    {
        update(idx, val, 0, 0, n - 1);
    }

    int query()
    {
        return tree[0].maxSum;
    }
};

void Solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (auto &x : a)
        cin >> x;

    SegmentTree segTree(a);
    int res = segTree.query();
    res = res < 0 ? 0 : res;
    ce1(res)

    while (m--)
    {
        int i, v;
        cin >> i >> v;
        segTree.update(i, v);
        int res = segTree.query();
        res = res < 0 ? 0 : res;
        ce1(res)
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