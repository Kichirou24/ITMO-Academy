#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;

    cin >> s;

    int B = 0, S = 0, C = 0;

    for (const auto &x : s)
    {
        if (x == 'B')
            B++;
        else if (x == 'S')
            S++;
        else
            C++;
    }

    int nb, ns, nc, pb, ps, pc;
    ;

    cin >> nb >> ns >> nc >> pb >> ps >> pc;

    long long rules;

    cin >> rules;

    auto check = [B, S, C, nb, ns, nc, pb, ps, pc, rules](long long cnt)
    {
        auto BB = max(B * cnt - nb, 0ll) * pb;
        auto SS = max(S * cnt - ns, 0ll) * ps;
        auto CC = max(C * cnt - nc, 0ll) * pc;

        return BB + SS + CC <= rules;
    };

    long long l = -1, r = rules + nb + ns + nc + 1;

    while (l + 1 < r)
    {
        auto m = l + (r - l) / 2;

        if (check(m))
            l = m;
        else
            r = m;
    }

    cout << l << endl;

    return 0;
}