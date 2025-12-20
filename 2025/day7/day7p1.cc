#include <bits/stdc++.h>
using ll = long long;

int main() {
    ifstream f {"day7.in"};
    string s;
    vector<vector<char>> grid;

    while (getline(f, s)) {
        if (s.empty()) break;
        vector<char> row(s.begin(), s.end());
        grid.push_back(row);
    }

    int r = grid.size(), c = grid[0].size();
    int sr = 0, sc = 0;
    for (int i = 0; i < c; i++) {
        if (grid[0][i] == 'S') {
            sc = i;
            break;
        }
    }

    int ans = 0;
    queue<pair<int,int>> q;
    vector<vector<bool>> vis(r, vector<bool>(c));
    q.push({sr, sc}); vis[sr][sc] = true;

    while (!q.empty()) {
        auto [cr, cc] = q.front(); q.pop();
        if (cr + 1 == r) continue;
        if (grid[cr+1][cc] == '^') {
            ans++;
            if (!vis[cr+1][cc-1]) {
                q.push({cr+1, cc-1});
                vis[cr+1][cc-1] = true;
            }
            if (!vis[cr+1][cc+1]) {
                q.push({cr+1, cc+1});
                vis[cr+1][cc+1] = true;
            }
        } else if (!vis[cr+1][cc]) {
            q.push({cr+1, cc});
            vis[cr+1][cc] = true;
        }
    }

    cout << ans << endl;
}
