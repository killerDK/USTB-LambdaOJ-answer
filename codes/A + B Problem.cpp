#include <bits/stdc++.h>
using namespace std;
const int N = 500 + 10;
char s1[N], s2[N];
int a[N], b[N], c[N];
int main()
{
    int la, lb, lc;
    cin >> s1 >> s2;
    la = strlen(s1);
    lb = strlen(s2);
    for (int i = 0; i < la; i++)
    {
        a[la - i] = s1[i] - '0';
    }
    for (int i = 0; i < lb; i++)
    {
        b[lb - i] = s2[i] - '0';
    }
    lc = max(la, lb) + 1;
    for (int i = 1; i <= lc; i++)
    {
        c[i] += a[i] + b[i];
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }
    if (c[lc] == 0 && lc > 1)
    {
        lc--;
    }
    for (int i = lc; i > 0; i--)
    {
        cout << c[i];
    }
}