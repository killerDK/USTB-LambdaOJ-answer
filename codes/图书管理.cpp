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
    while (iss >> bookId)
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