#include <bits/stdc++.h>
using ll = long long;

ll solve(int cr, int cc, int r, int c, vector<vector<char>> &grid, vector<vector<ll>> &memo) {
    if (cr + 1 == r) return 1;
    if (memo[cr][cc] != -1) return memo[cr][cc];

    ll ret = 0;
    if (grid[cr+1][cc] == '^') {
        ret = solve(cr+1, cc-1, r, c, grid, memo) + solve(cr+1, cc+1, r, c, grid, memo);
    } else {
        ret = solve(cr+1, cc, r, c, grid, memo);
    }

    return memo[cr][cc] = ret;
}

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

    vector<vector<ll>> memo(r, vector<ll>(c, -1));

    cout << solve(sr, sc, r, c, grid, memo) << endl;
}
