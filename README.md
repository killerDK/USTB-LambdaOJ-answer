# USTB-LambdaOJ （数据与算法课程实验部分题解）

------------

## 23年物联网与信安大二实验部分题题解，欢迎补充指正以及增加别的解题方式

提示：据验证，快读在读入这里的大部分题目时候性能不如关闭同步流的 cin\cout 。且这里大部分题目空间卡的都很死，推荐使用动态数组进行空间管理。本项目的**正解**均为老师课上讲的方法。

## 1. [A + B Problem](https://ustb.lambdaoj.com:9999/#/problem/1001)

使用高精度加法即可

```cpp
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
```

## 2. [The Nth Number in Fibonacci Sequence](https://ustb.lambdaoj.com:9999/#/problem/1002)

题目让求第 n 个斐波那契数，但是数据极大，普通的递推不能满足要求。
但是任意一个**齐次线性的整数递推数列**都有模周期。(关于某个数的取模存在周期性)
我们可以先编程求出 fib(n) MOD 9973 的周期，再计算。

```cpp
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
```

## 3. [寻找丢失的筷子](https://ustb.lambdaoj.com:9999/#/problem/1018)

找到两个没有被**配对的**数。
我这里采用的方法是用一个 map 存一下，读入一个元素，如果没被存过就标记为1，如果被存过（证明配对了）就清除，最后遍历 map 找到剩余的没有被配对的元素。
**正解为：异或**

```cpp
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
```

## 4. [图书管理](https://ustb.lambdaoj.com:9999/#/problem/1023)

找一种数据结构能快捷实现多次查找/添加/删除。底层为红黑树的 map 和 bitset 在查找/添加/删除有 O(logn) 的良好性质，因空间卡的死，且书籍只有存在与不存在两种情况，所以用 bitset 即可。

```cpp
#include <bits/stdc++.h>

using namespace std;
bitset<10000000 + 5> books;
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    string line;
    getline(cin, line);
    istringstream iss(line);
    int bookId;
    while (iss >> bookId)// 取出 string 中的 int
        books[bookId] = 1;

    int m;
    cin >> m;
    string res;
    for (int i = 1; i <= m; ++i)
    {
        int op, id;
        cin >> op >> id;

        if (op == 1)
        {
            cout << (books[id] ? 1 : 0);
        }
        else if (op == 2)
        {
            if (books[id])
            {
                books[id] = 0;
                cout << 1;
            }
            else
            {
                cout << 0;
            }
        }
        else if (op == 3)
        {
            if (!books[id])
            {
                books[id] = 1;
                cout << 1;
            }
            else
            {
                cout << 0;
            }
        }
    }

    return 0;
}
```

## 5. [寻找中位数](https://ustb.lambdaoj.com:9999/#/problem/1026)

m 次添加并查询中位数，我们这里采用**对顶堆**，每次加入一个数 x（addNum函数） ：若 x 大于大根堆堆顶 ，则加入小根堆，反之则加入大根堆，这样可以保证大根堆元素都小于小根堆的元素。并且维护堆的 size 差小于等于1。因为所有**比大根堆的最大值小的元素的最小值**在小根堆堆顶，且两个堆的 size 相当，于是这时在 size 稍大的堆的堆顶的元素就是中位数。
再来看题，给了我们需要查询的区间，假设我们第一次查询的是 0-n 的中位数，第二次查询的是 0-2 的中位数，我么会发现建立的对顶堆是 0-n 的，也就是我们只维护了 0-n 的中位数， 0-2 中的元素可能已经不知道跑到堆的哪里去了，还需要重新建堆，这样会严重耽误时间。
所以我们对 b 排个序并保留原始的顺序，从小到大依次查询，也就是从前到后慢慢建堆，保证一次建堆过程就能按顺序找到如 0-2 的中位数 、0-4 的中位数到 0-n 的中位数等所有想要的答案，最后按照原始顺序输出。

```cpp
#include <bits/stdc++.h>
using namespace std;

void addNum(int num, priority_queue<int> &maxHeap, priority_queue<int, vector<int>, greater<int>> &minHeap)
{
    if (maxHeap.empty() || num <= maxHeap.top())
        maxHeap.push(num);
    else
        minHeap.push(num);

    if (maxHeap.size() > minHeap.size() + 1)
    {
        minHeap.push(maxHeap.top());
        maxHeap.pop();
    }
    else if (minHeap.size() > maxHeap.size())
    {
        maxHeap.push(minHeap.top());
        minHeap.pop();
    }
}

double findMedian(const priority_queue<int> &maxHeap, const priority_queue<int, vector<int>, greater<int>> &minHeap)
{
    if (maxHeap.size() > minHeap.size())
        return maxHeap.top();
    else
        return (maxHeap.top() + minHeap.top()) / 2.0;
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> T(n);
    for (int i = 0; i < n; i++)
    {
        cin >> T[i];
    }
    vector<pair<int, int>> indexed_queries(m);
    for (int i = 0; i < m; i++)
    {
        int b;
        cin >> b;
        indexed_queries[i] = {b, i};
    }

    sort(indexed_queries.begin(), indexed_queries.end());

    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    vector<double> results(m);
    int currIndex = 0;

    for (const auto &query : indexed_queries)
    {
        int b = query.first;
        int originalIdx = query.second;// 记录原顺序

        while (currIndex <= b)
        {
            addNum(T[currIndex], maxHeap, minHeap);
            currIndex++;
        }

        results[originalIdx] = findMedian(maxHeap, minHeap);
    }

    for (double res : results)
    {
        cout << res << endl;
    }

    return 0;
}
```

## 6. [健康的饮食计划](https://ustb.lambdaoj.com:9999/#/problem/1022)

这道题难的是记录历史状态的部分：我们这里除了常规的 dp 数组外，再开一个 prev 数组用来记录到达当前状态的上一个状态，以及 choice 记录到达当前状态**时刻**选择的食物，这样我们就可以通过逐步回溯 prev 数组来找到 prev 数组对应的 choice 数组，就可以记录历史状态了。
状态转移部分：遍历所有可能的食物，我们找到满足所有需求状态下的最小食物组合，最后用目标状态回溯就行

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 16;
const int MAX_M = 65536;

vector<unsigned short> foods;
unsigned short target;
int n, m;

vector<int> dp;
vector<int> prev_state;
vector<int> choice;

void read_input()
{
    cin >> n >> m;
    int temp;
    for (int i = 0; i < m; i++)
    {
        cin >> temp;
    }

    target = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        target |= (1 << temp);
    }

    foods.resize(m, 0);
    for (int i = 0; i < m; i++)
    {
        string line;
        getline(cin >> ws, line);
        istringstream iss(line);
        while (iss >> temp)
        {
            foods[i] |= (1 << temp);
        }
    }
}

bool process()
{
    int total_states = 1 << MAX_N;
    dp.assign(total_states, INT_MAX);
    prev_state.assign(total_states, -1);
    choice.assign(total_states, -1);
    dp[0] = 0;

    for (int state = 0; state < total_states; state++)
    {
        if (dp[state] == INT_MAX)
            continue;

        for (int j = 0; j < m; j++)
        {
            int new_state = state | foods[j];
            if (dp[state] + 1 < dp[new_state])
            {
                dp[new_state] = dp[state] + 1;
                prev_state[new_state] = state;
                choice[new_state] = j;
            }
        }
    }

    return dp[target] != INT_MAX;
}

void print_result()
{
    vector<int> result;
    unsigned short current_state = target;

    while (current_state != 0)
    {
        result.push_back(choice[current_state]);
        current_state = prev_state[current_state];
    }

    sort(result.begin(), result.end());

    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i];
        if (i < result.size() - 1)
            cout << " ";
    }
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    read_input();
    if (process())
    {
        print_result();
    }

    return 0;
}

```

## 7. [图最短路径](https://ustb.lambdaoj.com:9999/#/problem/1010)

这道题十分怪异，他卡掉了常用的 dijkstra 算法，即使是堆优化的也过不了倒数**第二个**点，但是它奇特的能被 spfa （~~已死~~） 通过，推测他在倒数第二个点建了一个超长的链表。
**正解**：分析数据可以发现，边长只有 123 这三种情况，所以我们可以把边拆开，在点与点之间添加虚拟点，把它转化成一个步长为 1 的图，用 bfs 求解。**但是!** 据我所知，没有人用这个方法 AC ，因为拆边加点阶段的开销太大不能接受。但直接用 bfs 却可以直接过，不需要拆点。所以就莫名其妙的 AC 了。如果有人用拆点的话，欢迎补充改正。

```cpp
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
```
