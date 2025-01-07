#include <bits/stdc++.h>

using ll = long long;

const vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};

int main() {
    ifstream f {"day20.in"};
    string s;

    vector<vector<char>> grid;
    while (getline(f, s)) {
        vector<char> row;
        for (char ch: s) row.push_back(ch);
        grid.push_back(row);
    }

    int r = grid.size(), c = grid[0].size();
    int sr = 0, sc = 0, er = 0, ec = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == 'S') {
                sr = i; sc = j;
            } else if (grid[i][j] == 'E') {
                er = i; ec = j;
            }
        }
    }

    vector<vector<int>> dis(r, vector<int>(c, -1));
    queue<pair<int,int>> q;
    int best = 0;

    dis[er][ec] = 0;
    q.push({er, ec});

    while (!q.empty()) {
        pair<int,int> p = q.front(); q.pop();
        if (p.first == sr && p.second == sc) {
            best = dis[p.first][p.second];
            continue;
        }

        for (int k = 0; k < 4; k++) {
            int newr = p.first + dir[k][0], newc = p.second + dir[k][1];
            if (grid[newr][newc] != '#' && dis[newr][newc] == -1) {
                dis[newr][newc] = dis[p.first][p.second] + 1;
                q.push({newr, newc});
            }
        }
    }

    vector<vector<int>> fwd(r, vector<int>(c, -1));
    int ans = 0;
    fwd[sr][sc] = 0;
    q.push({sr, sc});

    while (!q.empty()) {
        pair<int,int> p = q.front(); q.pop();
        int row = p.first, col = p.second;
        if (fwd[row][col] > best) continue;

        for (int newr = row - 2; newr <= row + 2; newr++) {
            for (int newc = col - 2; newc <= col + 2; newc++) {
                int walk = abs(newr - row) + abs(newc - col);
                if (walk > 2) continue;
                if (!(newr >= 0 && newr < r && newc >= 0 && newc < c)) continue;
                if (grid[newr][newc] == '#') continue;
                if (fwd[row][col] + dis[newr][newc] + walk <= best - 100) {
                    ans++;
                }
            }
        }

        for (int k = 0; k < 4; k++) {
            int newr = row + dir[k][0], newc = col + dir[k][1];
            if (grid[newr][newc] != '#' && fwd[newr][newc] == -1) {
                fwd[newr][newc] = fwd[row][col] + 1;
                q.push({newr, newc});
            }
        }
    }

    cout << ans << endl;
}
