#include <bits/stdc++.h>

using ll = long long;

const vector<vector<int>> dir = {{0,1},{1,0},{0,-1},{-1,0}};

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
    int sr = 0, sc = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == 'S') {
                sr = i; sc = j;
                break;
            }
        }
    }

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    map<vector<int>, int> costs;

    pq.push({0, sr, sc, 0});
    costs[{sr, sc, 0}] = 0;
    int ans = INT_MAX;

    while (!pq.empty()) {
        vector<int> cur = pq.top(); pq.pop();
        int cost = cur[0], row = cur[1], col = cur[2], d = cur[3];
        if (grid[row][col] == 'E') {
            ans = min(ans, cost);
            continue;
        }

        int nr = row + dir[d][0], nc = col + dir[d][1];
        if (grid[nr][nc] != '#') {
            if (costs.find({nr, nc, d}) == costs.end() || costs[{nr, nc, d}] > cost + 1) {
                costs[{nr, nc, d}] = cost + 1;
                pq.push({cost + 1, nr, nc, d});
            }
        }

        for (int nd: {(d+1)%4, (d+3)%4}) {
            if (costs.find({row, col, nd}) == costs.end() || costs[{row, col, nd}] > cost + 1000) {
                costs[{row, col, nd}] = cost + 1000;
                pq.push({cost + 1000, row, col, nd});
            }
        }
    }

    cout << ans << endl;
}
