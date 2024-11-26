#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;

    cin >> n >> k;

    vector<int> a(k);

    for (int i = 0; i < k; i++)
        cin >> a[i];

    auto check = [&a, n](long long cnt)
    {
        int count = 0;
        long long last = 0;

        for (const auto &x : a)
        {
            if (x + last < cnt)
                last += x;
            else if (x > cnt)
                count++;
            else
            {
                count++;
                last = (x + last) % cnt;
            }

            if (count >= n)
                return true;
        }

        return false;
    };

    long long l = 0, r = (long long)*max_element(a.begin(), a.end()) * k / n + 1;

    while (l + 1 < r)
    {
        auto m = l + (r - l) / 2;

        if (check(m))
            l = m;
        else
            r = m;  
    }

    cout << l + 1 << endl;

    return 0;
}