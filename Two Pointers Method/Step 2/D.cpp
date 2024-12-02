#include <bits/stdc++.h>

using namespace std;

#define taskname "D"

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

void Solve()
{
    int n, s;
    cin >> n >> s;

    vector<int> a(n);
    for (auto &x : a)
        cin >> x;

    int i = 0, res = 0, sum = 0;

    for (int j = 0; j < n; ++j)
    {
        sum += a[j];
        while (sum - a[i] >= s)
            sum -= a[i++];
        
        if (sum >= s)
            res += (i + 1);
    }

    ce1(res)
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