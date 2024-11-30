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
        if (rx == lx + 1)
        {
            tree[x] += v;
            return;
        }

        int m = (lx + rx) / 2;
        if (id < m)
            update(2 * x + 1, lx, m, id, v);
        else
            update(2 * x + 2, m, rx, id, v);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void update(int id, int v)
    {
        update(0, 0, size, id, v);
    }

    int get(int x, int lx, int rx, int l, int r)
    {
        if (lx >= r || rx <= l)
            return 0;
        
        if (lx >= l && rx <= r)
            return tree[x];
        
        int m = (lx + rx) / 2;
        int get1 = get(2 * x + 1, lx, m, l, r);
        int get2 = get(2 * x + 2, m, rx, l, r);
        return get1 + get2;
    }

    int get(int l, int r)
    {
        return get(0, 0, size, l, r);
    }

    void show()
    {
        for (auto x : tree)
            cout << x << " ";
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
            int l, r, v;
            cin >> l >> r >> v;

            st.update(l, v);
            if (r < n)
                st.update(r, -v);
            // st.show();
            // ce1("")
        }
        else
        {
            int id;
            cin >> id;
            ce1(st.get(0, id + 1));
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