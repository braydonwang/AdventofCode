#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <regex>

using ll = long long;
using namespace std;

const vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};

int getScore(int row, int col, int r, int c, vector<vector<int>> &scores, vector<vector<char>> &grid) {
    if (scores[row][col] != -1) return scores[row][col];
    if (grid[row][col] == '9') return 1;

    int total = 0;
    for (int k = 0; k < dir.size(); k++) {
        int newrow = row + dir[k][0], newcol = col + dir[k][1];
        if (newrow >= 0 && newrow < r && newcol >= 0 && newcol < c && grid[newrow][newcol] == grid[row][col] + 1) {
            total += getScore(newrow, newcol, r, c, scores, grid);
        }
    }

    return scores[row][col] = total;
}

int main() {
    ifstream f {"day10.in"};
    string s;
    vector<vector<char>> grid;

    while (getline(f,s)) {
        vector<char> row;
        for (char ch: s) row.push_back(ch);
        grid.push_back(row);
    }

    int r = grid.size(), c = grid[0].size();
    vector<vector<int>> scores(r, vector<int>(c, -1));
    ll sum = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == '0') {
                sum += getScore(i, j, r, c, scores, grid);
            }
        }
    }

    cout << sum << endl;
}
