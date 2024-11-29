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

class SegmentTree
{
    int size;
    vector<int> tree;

public:
    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        tree.assign(2 * size, 0);
    }

    void update(int x, int lx, int rx, int id, int v)
    {
        if (lx== rx)
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

    int get(int x, int lx, int rx, int l, int r)
    {
        if ((rx <= l) || (lx >= r))
            return 0;

        if ((lx >= l) && (rx <= r))
            return tree[x];

        int m = (lx + rx) / 2;
        return get(2 * x, lx, m, l, r) + get(2 * x + 1, m + 1, rx, l, r);
    }

    int get(int l, int r)
    {
        return get(1, 0, size - 1, l, r);
    }
};

void Solve()
{
    int n;
    cin >> n;

    SegmentTree st;
    st.init(n);

    int v;
    for (int i = 0; i < n; ++i)
    {
        cin >> v;
        c1(st.get(v - 1, n))
        st.update(v - 1, 1);
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