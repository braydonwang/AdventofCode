#include <bits/stdc++.h>

using ll = long long;

const vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};

bool valid(int cnt, vector<pair<int,int>> &tiles) {
    vector<vector<bool>> grid(71, vector<bool>(71));
    vector<vector<bool>> vis(71, vector<bool>(71));

    for (int i = 0; i < cnt; i++) {
        int row = tiles[i].first, col = tiles[i].second;
        grid[row][col] = true;
    }

    queue<pair<int,int>> q;
    q.push({0, 0});
    vis[0][0] = true;

    while (!q.empty()) {
        pair<int,int> cur = q.front(); q.pop();
        int row = cur.first, col = cur.second;

        if (row == 70 && col == 70) {
            return true;
        }

        for (int k = 0; k < 4; k++) {
            int newr = row + dir[k][0], newc = col + dir[k][1];
            if (newr >= 0 && newr <= 70 && newc >= 0 && newc <= 70 && !grid[newr][newc] && !vis[newr][newc]) {
                vis[newr][newc] = true;
                q.push({newr, newc});
            }
        }
    }

    return false;
}

int main() {
    ifstream f {"day18.in"};
    string s;
    vector<pair<int,int>> tiles;

    while (getline(f, s)) {
        int idx = s.find(',');
        int row = stoi(s.substr(0, idx)), col = stoi(s.substr(idx+1));
        tiles.push_back({row, col});
    }

    int lo = 0, hi = tiles.size(), ans = 0;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (!valid(mid, tiles)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    cout << tiles[ans-1].first << "," << tiles[ans-1].second << endl;
}
