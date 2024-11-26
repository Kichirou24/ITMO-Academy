#include <bits/stdc++.h>

using namespace std;

double solve(const vector<pair<int, int>> &A, const int k)
{
    const auto n = A.size();
    auto Check = [&A, n, k](double avg)
    {
        vector<double> arr(n);
        for (auto i = 0; i < n; i++)
            arr[i] = avg * A[i].second - A[i].first;

        nth_element(arr.begin(), arr.begin() + k - 1, arr.end());

        double t = 0.0;

        for (auto i = 0; i < k; i++)
            t += arr[i];
        return t <= 0;
    };

    double lo = 9.9e-6, hi = 1e5;
    for (auto i = 0; i < 70; i++)
    {
        auto m = lo + (hi - lo) / 2;
        if (Check(m))
            lo = m;
        else
            hi = m;
    }
    return lo;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;

    cin >> n >> k;

    vector<pair<int, int>> A(n);
    for (int i = 0; i < n; i++)
        cin >> A[i].first >> A[i].second;

    cout << setprecision(11) << solve(A, k) << endl;

    return 0;
}