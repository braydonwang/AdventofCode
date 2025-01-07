#include <bits/stdc++.h>

using ll = long long;

void move(int &sr, int &sc, int dr, int dc, vector<vector<char>> &grid) {
    int newr = sr + dr, newc = sc + dc;
    if (grid[newr][newc] == '#') return;
    if (grid[newr][newc] == '.') {
        grid[newr][newc] = '@';
        grid[sr][sc] = '.';
        sr = newr; sc = newc;
        return;
    }

    if (dc != 0) {
        int curr = newr, curc = newc;
        while (grid[curr][curc] != '#') {
            if (grid[curr][curc] == '.') {
                while (curc != newc) {
                    grid[curr][curc] = grid[curr][curc-dc];
                    curc -= dc;
                }
                grid[newr][newc] = '@';
                grid[sr][sc] = '.';
                sr = newr; sc = newc;
                return;
            }
            curr += dr; curc += dc;
        }
    } else {
        queue<pair<int,int>> q;
        set<pair<int,int>> seen;
        bool blocked = false;

        seen.insert({newr, newc});
        q.push({newr, newc});

        while (!q.empty()) {
            pair<int,int> p = q.front(); q.pop();

            if (grid[p.first][p.second] == '[' && !seen.contains({p.first, p.second + 1})) {
                seen.insert({p.first, p.second + 1});
                q.push({p.first, p.second + 1});
            }

            if (grid[p.first][p.second] == ']' && !seen.contains({p.first, p.second - 1})) {
                seen.insert({p.first, p.second - 1});
                q.push({p.first, p.second - 1});
            }

            int nr = p.first + dr, nc = p.second;
            if (grid[nr][nc] == '#') {
                blocked = true;
                break;
            } else if ((grid[nr][nc] == '[' || grid[nr][nc] == ']') && !seen.contains({nr, nc})) {
                seen.insert({nr, nc});
                q.push({nr, nc});
            }
        }

        if (!blocked) {
            vector<vector<char>> tmp = grid;
            for (pair<int,int> p: seen) {
                grid[p.first][p.second] = '.';
            }
            for (pair<int,int> p: seen) {
                grid[p.first + dr][p.second] = tmp[p.first][p.second];
            }
            grid[newr][newc] = '@';
            grid[sr][sc] = '.';
            sr = newr; sc = newc;
        }
    }
}

int main() {
    ifstream f {"day15.in"};
    string s;
    vector<vector<char>> grid;
    
    while (getline(f, s)) {
        if (s.empty()) break;
        vector<char> row;
        for (char ch: s) {
            if (ch == '#' || ch == '.') {
                row.push_back(ch); row.push_back(ch); 
            } else if (ch == 'O') {
                row.push_back('['); row.push_back(']'); 
            } else {
                row.push_back(ch); row.push_back('.'); 
            }
        }
        grid.push_back(row);
    }

    int r = grid.size(), c = grid[0].size();
    int sr = 0, sc = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == '@') {
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
            if (grid[i][j] == '[') {
                ans += 100 * i + j;
            }
        }
    }

    cout << ans << endl;
}
