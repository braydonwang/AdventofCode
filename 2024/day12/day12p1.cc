#include <bits/stdc++.h>

using ll = long long;

const vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};

void dfs(int row, int col, int r, int c, ll &area, ll &perim, vector<vector<bool>> &vis, vector<vector<char>> &grid) {
    vis[row][col] = true;
    area++;

    for (int k = 0; k < 4; k++) {
        int newrow = row + dir[k][0], newcol = col + dir[k][1];
        bool inBounds = newrow >= 0 && newrow < r && newcol >= 0 && newcol < c;

        if (inBounds && grid[newrow][newcol] == grid[row][col] && !vis[newrow][newcol]) {
            dfs(newrow, newcol, r, c, area, perim, vis, grid);
        } else if (!inBounds || grid[newrow][newcol] != grid[row][col]) {
            perim++;
        }
    }
}

int main() {
    ifstream f {"day12.in"};
    string s;
    
    vector<vector<char>> grid;
    while (getline(f, s)) {
        vector<char> row;
        for (char ch: s) row.push_back(ch);
        grid.push_back(row);
    }

    int r = grid.size(), c = grid[0].size();
    ll ans = 0;
    vector<vector<bool>> vis(r, vector<bool>(c));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (!vis[i][j]) {
                ll area = 0, perim = 0;
                dfs(i, j, r, c, area, perim, vis, grid);
                ans += area * perim;
            }
        }
    }

    cout << ans << endl;
}
