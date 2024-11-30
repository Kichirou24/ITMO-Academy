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

int r;

struct Matrix
{
    int a, b, c, d;
};

struct SegmentTree
{
    int size;
    vector<Matrix> tree;

    Matrix add(Matrix a, Matrix b)
    {
        return {
            (a.a * b.a + a.b * b.c) % r,
            (a.a * b.b + a.b * b.d) % r,
            (a.c * b.a + a.d * b.c) % r,
            (a.c * b.b + a.d * b.d) % r};
    }

    void init(vector<Matrix> &a)
    {
        size = 1;
        while (size < a.size())
            size *= 2;
        tree.assign(2 * size, {1, 0, 0, 1});
        build(a, 0, 0, size);
    }

    void build(vector<Matrix> &a, int x, int lx, int rx)
    {
        if (rx == lx + 1)
        {
            if (lx < a.size())
                tree[x] = a[lx];
            return;
        }

        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);

        tree[x] = add(tree[2 * x + 1], tree[2 * x + 2]);
    }

    Matrix get(int x, int lx, int rx, int L, int R)
    {
        if (lx >= R || rx <= L)
            return {1, 0, 0, 1};

        if (lx >= L && rx <= R)
            return tree[x];

        int m = (lx + rx) / 2;

        Matrix get1 = get(2 * x + 1, lx, m, L, R);
        Matrix get2 = get(2 * x + 2, m, rx, L, R);
        return add(get1, get2);
    }

    Matrix get(int L, int R)
    {
        return get(0, 0, size, L, R);
    }

    void show()
    {
        for (auto x : tree)
            printf("%d %d\n%d %d\n\n", x.a, x.b, x.c, x.d);
    }
};

void Solve()
{
    int n, m;
    cin >> r >> n >> m;

    vector<Matrix> a(n);

    for (int i = 0; i < n; ++i)
        scanf("%lld %lld %lld %lld", &a[i].a, &a[i].b, &a[i].c, &a[i].d);

    for (int i = 0; i < n; ++i)
        printf("%d %d\n%d %d\n\n", a[i].a, a[i].b, a[i].c, a[i].d);

    SegmentTree st;
    st.init(a);

    // st.show();

    while (m--)
    {
        int L, R;
        cin >> L >> R;
        Matrix res = st.get(L - 1, R);
        printf("%d %d\n%d %d\n\n", res.a, res.b, res.c, res.d);
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