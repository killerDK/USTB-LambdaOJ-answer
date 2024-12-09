#include <bits/stdc++.h>
using namespace std;
const int N = 100000 + 10;
const int INF = 2147483647;
map<int, int> hash_;
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n * 2 - 2; i++)
    {
        int x;
        cin >> x;
        if (hash_[x] == 0)
            hash_[x] = 1;
        else
            hash_[x] = 0;
    }
    auto it = hash_.begin();
    for (; it != hash_.end(); it++)
    {
        if (it->second == 1)
            cout << it->first << endl;
    }
}