#include <bits/stdc++.h>
using namespace std;

// 优化输入输出
static const auto io_sync_off = []()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return nullptr;
}();

class Solution
{
private:
    static const int MAX_N = 16;
    static const int MAX_M = 65536;
    vector<unsigned short> foods; // 每种食物包含的营养素状态
    unsigned short target;        // 目标营养素状态
    int n, m;                     // n: 营养素数量, m: 食物数量

    // DP数组
    vector<int> dp;     // dp[s]表示达到状态s所需的最少食物数量
    vector<int> prev;   // prev[s]记录达到状态s时上一个状态
    vector<int> choice; // choice[s]记录达到状态s时选择的食物

public:
    void solve()
    {
        read_input();
        if (process())
        {
            print_result();
        }
        else
        {
            cout << -1 << endl;
        }
    }

private:
    void read_input()
    {
        cin >> n >> m;
        int temp;
        for (int i = 0; i < m; i++)
        {
            cin >> temp; // 读取但不使用每种食物的营养素数量
        }

        // 读取目标营养素列表
        target = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> temp;
            target |= (1 << temp);
        }

        // 读取每种食物的营养素列表
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
        prev.assign(total_states, -1);
        choice.assign(total_states, -1);
        dp[0] = 0;

        // 遍历所有可能的状态
        for (int state = 0; state < total_states; state++)
        {
            if (dp[state] == INT_MAX)
                continue;

            // 尝试每种食物
            for (int j = 0; j < m; j++)
            {
                int new_state = state | foods[j];
                if (dp[state] + 1 < dp[new_state])
                {
                    dp[new_state] = dp[state] + 1;
                    prev[new_state] = state;
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
            current_state = prev[current_state];
        }

        sort(result.begin(), result.end());

        for (int i = 0; i < result.size(); i++)
        {
            cout << result[i];
            if (i < result.size() - 1)
            {
                cout << " ";
            }
        }
        cout << endl;
    }
};

int main()
{
    Solution solution;
    solution.solve();
    return 0;
}