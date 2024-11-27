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

void Solve()
{
    string t;
    cin >> t;

    int n;
    cin >> n;

    int m = t.size();
    vector<int> suffixArr(m), p(m), c(m);

    iota(suffixArr.begin(), suffixArr.end(), 0);
    sort(suffixArr.begin(), suffixArr.end(), [&t](int a, int b)
         { return t[a] < t[b]; });

    for (int i = 0; i < m; ++i)
        if (i == 0 || t[suffixArr[i]] != t[suffixArr[i - 1]])
            p[suffixArr[i]] = i;
        else
            p[suffixArr[i]] = p[suffixArr[i - 1]];

    for (int k = 1; k < m; k *= 2)
    {
        auto cmp = [&p, k, m](int a, int b)
        {
            if (p[a] != p[b])
                return p[a] < p[b];

            if (a + k < m && b + k < m)
                return p[a + k] < p[b + k];
            else
                return a > b;
        };

        sort(suffixArr.begin(), suffixArr.end(), cmp);

        c[suffixArr[0]] = 0;

        for (int i = 1; i < m; ++i)
            c[suffixArr[i]] = c[suffixArr[i - 1]] + cmp(suffixArr[i - 1], suffixArr[i]);
        p = c;
    }

    // for (auto x : suffixArr)
    //     cout << x << " " << t.substr(x) << endl;

    while (n--)
    {
        string si;
        cin >> si;

        int l = 0, r = t.size();
        while (l < r)
        {
            int m = (l + r) / 2;
            if (t.compare(suffixArr[m], si.size(), si) < 0)
                l = m + 1;
            else
                r = m;
        }

        int st = l;
        r = t.size();
        while (l < r)
        {
            int m = (l + r) / 2;
            if (t.compare(suffixArr[m], si.size(), si) <= 0)
                l = m + 1;
            else
                r = m;
        }

        int en = l;
        
        ce1(en - st)
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