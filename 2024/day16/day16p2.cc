#include <bits/stdc++.h>

using ll = long long;

int ans = INT_MAX;
set<pair<int,int>> tiles;

const vector<vector<int>> dir = {{0,1},{1,0},{0,-1},{-1,0}};

bool inBounds(int row, int col, int r, int c) {
    return row >= 0 && row < r && col >= 0 && col < c;
}

bool solve(int row, int col, int curdir, int er, int ec, int r, int c, vector<vector<char>> &grid, vector<vector<vector<int>>> &dp) {
    if (row == er && col == ec) {
        if (dp[row][col][curdir] < ans) {
            ans = dp[row][col][curdir];
            tiles.clear();
            return true;
        } else if (dp[row][col][curdir] == ans) {
            return true;
        }
        return false;
    }

    bool good = false;

    int newrow = row + dir[curdir][0], newcol = col + dir[curdir][1];
    if (inBounds(newrow, newcol, r, c) && grid[newrow][newcol] != '#' && dp[row][col][curdir] + 1 <= dp[newrow][newcol][curdir]) {
        dp[newrow][newcol][curdir] = dp[row][col][curdir] + 1;
        good |= solve(newrow, newcol, curdir, er, ec, r, c, grid, dp);
    }

    int newdir = (curdir + 3) % 4;
    if (dp[row][col][curdir] + 1000 <= dp[row][col][newdir]) {
        dp[row][col][newdir] = dp[row][col][curdir] + 1000;
        good |= solve(row, col, newdir, er, ec, r, c, grid, dp);
    }

    newdir = (curdir + 1) % 4;
    if (dp[row][col][curdir] + 1000 <= dp[row][col][newdir]) {
        dp[row][col][newdir] = dp[row][col][curdir] + 1000;
        good |= solve(row, col, newdir, er, ec, r, c, grid, dp);
    }

    if (good) tiles.insert({row, col});
    return good;
}

int main() {
    ifstream f {"day16.in"};
    string s;
    vector<vector<char>> grid;
    
    while (getline(f, s)) {
        if (s.empty()) break;
        vector<char> row;
        for (char ch: s) row.push_back(ch);
        grid.push_back(row);
    }

    int r = grid.size(), c = grid[0].size();
    vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(4, INT_MAX)));
    
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

    int curdir = 0;
    dp[sr][sc][curdir] = 0;

    solve(sr, sc, curdir, er, ec, r, c, grid, dp);

    // for (pair<int,int> p: tiles) {
    //     grid[p.first][p.second] = 'O';
    // }

    // for (int i = 0; i < r; i++) {
    //     for (int j = 0; j < c; j++) {
    //         cout << grid[i][j];
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    cout << tiles.size() + 1 << endl;
}
