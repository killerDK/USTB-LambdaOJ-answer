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
        int originalIdx = query.second;

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