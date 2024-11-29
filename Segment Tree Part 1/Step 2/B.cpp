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
    vector<int> sums;

public:
    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        sums.assign(2 * size, 0LL);
    }

    void build(vector<int> &a, int x, int lx, int rx)
    {
        if (rx == lx)
            sums[x] = a[lx];
        else
        {
            int m = (lx + rx) / 2;
            build(a, 2 * x, lx, m);
            build(a, 2 * x + 1, m + 1, rx);

            sums[x] = sums[2 * x] + sums[2 * x + 1];
        }
    }

    void update(vector<int> &a, int x, int lx, int rx, int pos)
    {
        if (lx == rx)
            sums[x] = 1 - sums[x];
        else
        {
            int m = (lx + rx) / 2;
            if (pos <= m)
                update(a, 2 * x, lx, m, pos);
            else
                update(a, 2 * x + 1, m + 1, rx, pos);

            sums[x] = sums[2 * x] + sums[2 * x + 1];
        }
    }

    int find(int x, int lx, int rx, int k)
    {
        if (lx == rx)
            return lx;

        int m = (lx + rx) / 2;
        if (sums[2 * x] > k)
            return find(2 * x, lx, m, k);
        else
            return find(2 * x + 1, m + 1, rx, k - sums[2 * x]);
    }
};

void Solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    SegmentTree st;
    st.init(n);

    st.build(a, 1, 0, n - 1);

    while (m--)
    {
        int op;
        cin >> op;

        if (op == 1)
        {
            int i;
            cin >> i;

            st.update(a, 1, 0, n - 1, i);
        }
        else
        {
            int k;
            cin >> k;

            ce1(st.find(1, 0, n - 1, k))
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