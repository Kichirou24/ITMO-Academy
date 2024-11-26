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

struct item
{
    int val, idx;
};

class SegmentTree
{
    int size;
    vector<item> values;

    item merge(item a, item b)
    {
        if (a.val < b.val)
            return a;
        if (a.val > b.val)
            return b;
        return {a.val, a.idx + b.idx};
    }

    item single(int v)
    {
        return {v, 1};
    }

    item NEUTRAL_ELEMENT = {INT_MAX, 0};

public:
    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        values.resize(2 * size);
    }

    void build(vector<int> &a, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < (int)a.size())
                values[x] = single(a[lx]);
            return;
        }

        int m = (lx + rx) / 2;

        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);

        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void build(vector<int> &a)
    {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            values[x] = single(v);
            return;
        }

        int m = (lx + rx) / 2;
        if (i < m)
            set(i, v, 2 * x + 1, lx, m);
        else
            set(i, v, 2 * x + 2, m, rx);

        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void set(int i, int v)
    {
        set(i, v, 0, 0, size);
    }

    item calc(int l, int r, int x, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return NEUTRAL_ELEMENT;
        if (lx >= l && rx <= r)
            return values[x];

        int m = (lx + rx) / 2;
        item s1 = calc(l, r, 2 * x + 1, lx, m);
        item s2 = calc(l, r, 2 * x + 2, m, rx);

        return min(s1, s2);
    }

    item calc(int l, int r)
    {
        return calc(l, r, 0, 0, size);
    }
};

void Solve()
{
    int n, m;
    cin >> n >> m;

    SegmentTree st;
    st.init(n);

    vector<int> a(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];

    st.build(a);

    while (m--)
    {
        int op;
        cin >> op;

        if (op == 1)
        {
            int i, v;
            cin >> i >> v;

            st.set(i, v);
        }
        else
        {
            int l, r;
            cin >> l >> r;

            auto res = st.calc(l, r);
            ce2(res.val, res.idx)
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