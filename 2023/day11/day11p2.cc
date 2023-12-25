#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <unordered_map>
#include <regex>
#include <string>

using namespace std;
#define ll long long

vector<string> split(string s);

int main() {
    ifstream f {"day11.in"};
    string s;
    vector<vector<char>> grid;
    vector<pair<int,int>> galaxies;
    int row = 0, col = 0;

    while (getline(f,s)) {
        vector<char> vec;
        col = s.length();
        
        for (int i = 0; i < s.length(); i++) {
            vec.push_back(s[i]);
            if (s[i] == '#') galaxies.push_back({row,i});
        }
        grid.push_back(vec);
        row++;
    }

    vector<int> noRow(row+1);
    vector<int> noCol(col+1);

    for (int i = 0; i < row; i++) {
        bool has = false;
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == '#') {
                has = true; break;
            }
        }
        if (!has) noRow[i+1]++;
    }
    for (int i = 0; i < col; i++) {
        bool has = false;
        for (int j = 0; j < row; j++) {
            if (grid[j][i] == '#') {
                has = true; break;
            }
        }
        if (!has) noCol[i+1]++;
    }

    for (int i = 1; i <= row; i++) {
        noRow[i] += noRow[i-1];
    }
    for (int i = 1; i <= col; i++) {
        noCol[i] += noCol[i-1];
    }

    ll ans = 0;
    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i+1; j < galaxies.size(); j++) {
            int r1 = galaxies[i].first, c1 = galaxies[i].second, r2 = galaxies[j].first, c2 = galaxies[j].second;
            ans += abs(r1 - r2) + abs(c1 - c2);

            int maxRow = max(r1,r2), minRow = min(r1,r2), maxCol = max(c1,c2), minCol = min(c1,c2);
            ans += (1000000-1) * (noRow[maxRow+1] - noRow[minRow] + noCol[maxCol+1] - noCol[minCol]);
        }
    }

    cout << ans << endl;
    
    return 0;
}

vector<string> split(string s) {
    stringstream ss(s);
    string str;
    vector<string> vec;

    while (ss >> str) {
        vec.push_back(str);
    }
    return vec;
}
