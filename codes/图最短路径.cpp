#include <bits/stdc++.h>
using namespace std;

const int INF = 2147483647;
int n, m, q;
struct Edge
{
    int to, weight;
};

vector<int> bfs(int start, const vector<Edge> graph[], int n)

{
    vector<int> dis(n + 1, INF);
    queue<int> q;

    dis[start] = 0;
    q.push(start);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto v : graph[u])
        {
            if (dis[v.to] > dis[u] + v.weight)
            {
                dis[v.to] = dis[u] + v.weight;
                q.push(v.to);
            }
        }
    }
    return dis;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    cin >> n >> m >> q;
    vector<Edge> g[n + 1];
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++)
    {
        cin >> queries[i].first >> queries[i].second;
    }
    for (auto query : queries)
    {
        cout << bfs(query.first, g, n)[query.second] << endl;
    }
}