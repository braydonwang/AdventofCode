#include <bits/stdc++.h>

using ll = long long;

const vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};

int main() {
    ifstream f {"day18.in"};
    string s;

    int cnt = 1024;
    vector<vector<bool>> grid(71, vector<bool>(71));
    vector<vector<bool>> vis(71, vector<bool>(71));

    while (cnt--) {
        getline(f, s);
        int idx = s.find(',');
        int row = stoi(s.substr(0, idx)), col = stoi(s.substr(idx+1));
        grid[row][col] = true;
    }

    queue<vector<int>> q;
    q.push({0, 0, 0});
    vis[0][0] = true;

    while (!q.empty()) {
        vector<int> cur = q.front(); q.pop();
        int row = cur[0], col = cur[1], dis = cur[2];

        if (row == 70 && col == 70) {
            cout << dis << endl;
            break;
        }

        for (int k = 0; k < 4; k++) {
            int newr = row + dir[k][0], newc = col + dir[k][1];
            if (newr >= 0 && newr <= 70 && newc >= 0 && newc <= 70 && !grid[newr][newc] && !vis[newr][newc]) {
                vis[newr][newc] = true;
                q.push({newr, newc, dis + 1});
            }
        }
    }
}
