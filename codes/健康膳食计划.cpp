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
