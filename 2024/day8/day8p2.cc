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

bool inBounds(int row, int col, int r, int c) {
    return row >= 0 && row < r && col >= 0 && col < c;
}

int main() {
    ifstream f {"day8.in"};
    string s;
    vector<vector<char>> grid;

    while (getline(f,s)) {
        vector<char> row;
        for (char ch: s) row.push_back(ch);
        grid.push_back(row);
    }

    set<pair<int,int>> antinodes;
    unordered_map<char, vector<pair<int,int>>> locs;
    int r = grid.size(), c = grid[0].size();

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] != '.') {
                locs[grid[i][j]].push_back({i, j});
            }
        }
    }

    for (auto &[_, ants]: locs) {
        for (int i = 0; i < ants.size() - 1; i++) {
            for (int j = i+1; j < ants.size(); j++) {
                int r1 = ants[i].first, c1 = ants[i].second, r2 = ants[j].first, c2 = ants[j].second;
                int diffr = r1 - r2, diffc = c1 - c2;

                while (inBounds(r1, c1, r, c)) {
                    antinodes.insert({r1, c1});
                    r1 += diffr; c1 += diffc;
                }
                while (inBounds(r2, c2, r, c)) {
                    antinodes.insert({r2, c2});
                    r2 -= diffr; c2 -= diffc;
                }
            }
        }
    }

    cout << antinodes.size() << endl;
}
