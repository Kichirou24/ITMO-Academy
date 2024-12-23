#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < k; i++)
    {
        int x;
        cin >> x; 
        bool check = false;
        
        int l = 0;
        int r = n - 1;

        while (r >= l)
        {
            int m = (l + r) / 2;

            if (a[m] == x)
            {
                check = true;
                break;
            }
            else if (a[m] < x)
            {
                l = m + 1;
            }
            else if (a[m] > x)
            {
                r = m - 1;
            }
        }

        if (check) cout << "YES\n";
        else cout << "NO\n";

    }

    return 0;
}