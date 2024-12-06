#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <regex>

using ll = long long;

using namespace std;

bool inBounds(int row, int col, int r, int c) {
    return row >= 0 && row < r && col >= 0 && col < c;
}

int main() {
    ifstream f {"day6.in"};
    string s;
    ll sum = 0;
    vector<vector<char>> grid;

    while (getline(f,s)) {
        vector<char> row;
        for (char ch: s) row.push_back(ch);
        grid.push_back(row);
    }

    int r = grid.size(), c = grid[0].size();
    int sr = 0, sc = 0;
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == '^') {
                sr = i; sc = j;
            }
        }
    }

    const vector<vector<int>> dir = {{-1,0},{0,1},{1,0},{0,-1}};
    int curdir = 0, row = sr, col = sc;

    while (inBounds(row, col, r, c)) {
        if (grid[row][col] != 'X') {
            grid[row][col] = 'X';
            sum++;
        }
        int newr = row + dir[curdir][0], newc = col + dir[curdir][1];
        if (inBounds(newr, newc, r, c) && grid[newr][newc] == '#') {
            curdir = (curdir + 1) % 4;
        } else {
            row = newr; col = newc;
        }
    }

    cout << sum << endl;
}
