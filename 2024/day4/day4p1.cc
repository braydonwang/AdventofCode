#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <regex>

using ll = long long;

using namespace std;
vector<int> split(string s);

const string xmas = "XMAS";
const vector<vector<int>> dir = {{1,0},{0,1},{0,-1},{-1,0},{1,1},{-1,-1},{1,-1},{-1,1}};

bool valid(int ind, int row, int col, int r, int c, int k, vector<vector<char>> &grid) {
    if (ind >= xmas.length()) return true;
    if (row < 0 || row >= r || col < 0 || col >= c) return false;
    if (grid[row][col] != xmas[ind]) return false;

    int newr = row + dir[k][0], newc = col + dir[k][1];
    return valid(ind+1, newr, newc, r, c, k, grid);
}

int main() {
    ifstream f {"day4.in"};
    string s;
    vector<vector<char>> grid;

    while (getline(f,s)) {
        vector<char> row;
        for (char ch: s) {
            row.push_back(ch);
        }
        grid.push_back(row);
    }

    int r = grid.size(), c = grid[0].size(), sum = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == 'X') {
                for (int k = 0; k < 8; k++) {
                    if (valid(0, i, j, r, c, k, grid)) {
                        sum++;
                    }
                }
            }
        }
    }

    cout << sum << endl;
}

vector<int> split(string s) {
    stringstream ss(s);
    int x;
    vector<int> vec;

    while (ss >> x) {
        vec.push_back(x);
    }
    return vec;
}
