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

void getScore(int row, int col, int r, int c, set<pair<int,int>> &ends, vector<vector<char>> &grid) {
    if (grid[row][col] == '9') {
        ends.insert({row, col});
        return;
    }

    for (int k = 0; k < dir.size(); k++) {
        int newrow = row + dir[k][0], newcol = col + dir[k][1];
        if (newrow >= 0 && newrow < r && newcol >= 0 && newcol < c && grid[newrow][newcol] == grid[row][col] + 1) {
            getScore(newrow, newcol, r, c, ends, grid);
        }
    }
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
    ll sum = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == '0') {
                set<pair<int,int>> ends;
                getScore(i, j, r, c, ends, grid);
                sum += ends.size();
            }
        }
    }

    cout << sum << endl;
}
