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

const vector<vector<int>> dir = {{-1,0},{0,1},{1,0},{0,-1}};

bool inBounds(int row, int col, int r, int c) {
    return row >= 0 && row < r && col >= 0 && col < c;
}

bool cycle(int row, int col, int curdir, int r, int c, vector<vector<char>> &grid, vector<vector<vector<bool>>> vis) {
    while (inBounds(row, col, r, c)) {
        if (vis[row][col][curdir]) {
            return true;
        }
        vis[row][col][curdir] = true;

        int newr = row + dir[curdir][0], newc = col + dir[curdir][1];
        if (inBounds(newr, newc, r, c) && grid[newr][newc] == '#') {
            curdir = (curdir + 1) % 4;
        } else {
            row = newr; col = newc;
        }
    }

    return false;
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

    for (int i = 0; i < r; i++) {
        cout << i << endl;
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == '.') {
                grid[i][j] = '#';

                int curdir = 0, row = sr, col = sc;
                vector<vector<vector<bool>>> vis(r, vector<vector<bool>>(c, vector<bool>(4, false)));
                bool cycle = false;

                while (inBounds(row, col, r, c)) {
                    if (vis[row][col][curdir]) {
                        cycle = true;
                        break;
                    }
                    vis[row][col][curdir] = true;

                    int newr = row + dir[curdir][0], newc = col + dir[curdir][1];
                    if (inBounds(newr, newc, r, c) && grid[newr][newc] == '#') {
                        curdir = (curdir + 1) % 4;
                    } else {
                        row = newr; col = newc;
                    }
                }

                if (cycle) sum++;
                grid[i][j] = '.';
            }
        }
    }

    cout << sum << endl;
}
