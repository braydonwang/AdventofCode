#include <bits/stdc++.h>
using ll = long long;

int main() {
    ifstream f {"day4.in"};
    string s;
    vector<string> grid;

    while (getline(f, s)) {
        if (s.empty()) break;
        grid.push_back(s);
    }

    vector<vector<int>> dir = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
    int r = grid.size(), c = grid[0].length();
    int ans = 0;
    bool updated = true;

    while (updated) {
        updated = false;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (grid[i][j] == '@') {
                    int cnt = 0;
                    for (int k = 0; k < dir.size(); k++) {
                        int newr = i + dir[k][0], newc = j + dir[k][1];
                        if (newr < 0 || newr >= r || newc < 0 || newc >= c) continue;
                        if (grid[newr][newc] == '@') {
                            cnt++;
                        }
                    }
                    if (cnt < 4) {
                        ans++;
                        grid[i][j] = '.';
                        updated = true;
                    }
                }
            }
        }
    }

    cout << ans << endl;
}
