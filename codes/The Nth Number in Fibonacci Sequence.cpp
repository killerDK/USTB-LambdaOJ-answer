#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 100000 + 10;
const int INF = 2147483647;
const int MOD = 9973;
int fib[N];
bool vis[N];
int fibmem(int n)
{
    if (vis[n])
        return fib[n];
    else
    {
        vis[n] = 1;
        return fib[n] = (fibmem(n - 1) + fibmem(n - 2)) % MOD;
    }
}
void solve()
{
    int n;
    cin >> n;
    cout << fibmem(n % 19948) << endl;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    fib[0] = 0;
    fib[1] = 1;
    vis[0] = 1;
    vis[1] = 1;
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}