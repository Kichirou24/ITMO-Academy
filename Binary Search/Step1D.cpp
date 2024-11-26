#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n, k;
    cin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    cin >> k;

    for (int i = 0; i < k; ++i)
    {
        int l, r;

        cin >> l >> r;

        auto left = lower_bound(a.begin(), a.end(), l);
        auto right = upper_bound(a.begin(), a.end(), r);

        cout << right - left << " ";
    }

    return 0;
}