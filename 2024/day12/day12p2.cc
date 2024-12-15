#include <bits/stdc++.h>

using ll = long long;

const vector<vector<int>> dir = {{0,1},{1,0},{0,-1},{-1,0}};

bool inBounds(int row, int col, int r, int c) {
    return row >= 0 && row < r && col >= 0 && col < c;
}

void dfs(int row, int col, int r, int c, ll &area, ll &corners, vector<vector<bool>> &vis, vector<vector<char>> &grid) {
    vis[row][col] = true;
    area++;

    for (int k = 0; k < 4; k++) {
        int r1 = row + dir[k][0], c1 = col + dir[k][1];
        int r2 = row + dir[(k+1)%4][0], c2 = col + dir[(k+1)%4][1];

        if ((!inBounds(r1, c1, r, c) || grid[r1][c1] != grid[row][col]) && (!inBounds(r2, c2, r, c) || grid[r2][c2] != grid[row][col])) {
            corners++;
        }

        if ((inBounds(r1, c1, r, c) && grid[r1][c1] == grid[row][col]) && (inBounds(r2, c2, r, c) && grid[r2][c2] == grid[row][col])) {
            int r3 = row + dir[k][0] + dir[(k+1)%4][0], c3 = col + dir[k][1] + dir[(k+1)%4][1];
            if (grid[r3][c3] != grid[row][col]) {
                corners++;
            }
        }
    }

    for (int k = 0; k < 4; k++) {
        int newrow = row + dir[k][0], newcol = col + dir[k][1];
        bool inBounds = newrow >= 0 && newrow < r && newcol >= 0 && newcol < c;

        if (inBounds && grid[newrow][newcol] == grid[row][col] && !vis[newrow][newcol]) {
            dfs(newrow, newcol, r, c, area, corners, vis, grid);
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
                ll area = 0, corners = 0;
                dfs(i, j, r, c, area, corners, vis, grid);
                ans += area * corners;
            }
        }
    }

    cout << ans << endl;
}
