#include <bits/stdc++.h>

using ll = long long;

void move(int &sr, int &sc, int dr, int dc, vector<vector<char>> &grid) {
    int newr = sr + dr, newc = sc + dc;
    if (grid[newr][newc] == '#') return;
    if (grid[newr][newc] == '.') {
        sr = newr; sc = newc;
        return;
    }

    int curr = newr, curc = newc;
    while (grid[curr][curc] != '#') {
        if (grid[curr][curc] == '.') {
            grid[curr][curc] = 'O';
            grid[newr][newc] = '.';
            sr = newr; sc = newc;
            return;
        }
        curr += dr; curc += dc;
    }
}

int main() {
    ifstream f {"day15.in"};
    string s;
    vector<vector<char>> grid;
    
    while (getline(f, s)) {
        if (s.empty()) break;
        vector<char> row;
        for (char ch: s) row.push_back(ch);
        grid.push_back(row);
    }

    int r = grid.size(), c = grid[0].size();
    int sr = 0, sc = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == '@') {
                grid[i][j] = '.';
                sr = i; sc = j;
            }
        }
    }

    while (getline(f, s)) {
        for (char ch: s) {
            int dr = 0, dc = 0;
            switch (ch) {
                case '<':
                    dc = -1; break;
                case '^':
                    dr = -1; break;
                case '>':
                    dc = 1; break;
                case 'v':
                    dr = 1; break;
            }

            move(sr, sc, dr, dc, grid);
        }
    }

    ll ans = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == 'O') {
                ans += 100 * i + j;
            }
        }
    }

    cout << ans << endl;
}
