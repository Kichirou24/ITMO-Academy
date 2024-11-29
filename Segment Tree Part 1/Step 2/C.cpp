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

class SegmentTree
{
    int size;
    vector<int> segTree;

public:
    void init(vector<int> &a)
    {
        size = 1;
        while (size < a.size())
            size *= 2;
        segTree.assign(2 * size, 0);
        build(a, 0, 0, size);
    }

    void build(vector<int> &a, int x, int lx, int rx)
    {
        if (rx == lx + 1)
        {
            if (lx < a.size())
                segTree[x] = a[lx];
            return;
        }

        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        segTree[x] = max(segTree[2 * x + 1], segTree[2 * x + 2]);
    }

    void build(vector<int> &a)
    {
        build(a, 0, 0, size);
    }

    void update(int x, int lx, int rx, int i, int v)
    {
        if (rx == lx + 1)
        {
            segTree[x] = v;
            return;
        }

        int m = (lx + rx) / 2;
        if (i < m)
            update(2 * x + 1, lx, m, i, v);
        else
            update(2 * x + 2, m, rx, i, v);

        segTree[x] = max(segTree[2 * x + 1], segTree[2 * x + 2]);
    }

    void update(int i, int v)
    {
        update(0, 0, size, i, v);
    }

    int find(int x, int lx, int rx, int v)
    {
        if (segTree[x] < v)
            return -1;

        if (rx == lx + 1)
            return lx;

        int m = (lx + rx) / 2;
        int res = find(2 * x + 1, lx, m, v);
        if (res == -1)
            res = find(2 * x + 2, m, rx, v);
        return res;
    }
    
    int find(int v)
    {
        return find(0, 0, size, v);
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
            int i, v;
            cin >> i >> v;
            st.update(i, v);
        }
        else
        {
            int v;
            cin >> v;
            ce1(st.find(v))
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