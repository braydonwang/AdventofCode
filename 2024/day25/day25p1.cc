#include <bits/stdc++.h>

using ll = long long;

const vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};

int main() {
    ifstream f {"day25.in"};
    string s;
    vector<vector<int>> keys, locks;

    while (getline(f, s)) {
        vector<vector<char>> grid;
        do {
            if (s.empty()) break;
            vector<char> row;
            for (char ch: s) row.push_back(ch);
            grid.push_back(row);
        } while (getline(f, s));

        bool lock = (grid[0][0] == '#');
        vector<int> vec;

        if (lock) {
            for (int i = 0; i < grid[0].size(); i++) {
                int j = 1;
                while (grid[j][i] == '#') j++;
                vec.push_back(j - 1);
            }
            locks.push_back(vec);
        } else {
            for (int i = 0; i < grid[0].size(); i++) {
                int j = grid.size() - 2;
                while (grid[j][i] == '#') j--;
                vec.push_back(grid.size() - 2 - j);
            }
            keys.push_back(vec);
        }
    }

    int ans = 0;
    for (vector<int> &key: keys) {
        for (vector<int> &lock: locks) {
            for (int i = 0; i < key.size(); i++) {
                if (key[i] + lock[i] > 5) {
                    ans++;
                    break;
                }
            }
        }
    }

    cout << keys.size() * locks.size() - ans << endl;
}
