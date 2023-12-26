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
vector<int> splitInt(string s, char ch);

string conv(vector<char> &vec) {
    string str = "";
    for (char ch: vec) str += ch;
    return str;
}

bool check(vector<vector<char>> &grid, int ind) {
    int l = ind, r = ind+1;
    while (l >= 0 && r < grid.size()) {
        if (conv(grid[l]) != conv(grid[r])) {
            return false;
        }
        l--; r++;
    }
    return true;
}

vector<vector<char>> transpose(vector<vector<char>> &grid) {
    vector<vector<char>> newGrid;
    for (int i = 0; i < grid[0].size(); i++) {
        vector<char> row;
        for (int j = 0; j < grid.size(); j++) {
            row.push_back(grid[j][i]);
        }
        newGrid.push_back(row);
    }
    return newGrid;
}

int find(vector<vector<char>> &grid) {
    int r = grid.size(), c = grid[0].size();
    int ret = 0;
    for (int i = 0; i < r-1; i++) {
        if (check(grid,i)) {
            ret = 100 * (i + 1);
            return ret;
        }
    }
    vector<vector<char>> newGrid = transpose(grid);
    for (int i = 0; i < c-1; i++) {
        if (check(newGrid,i)) {
            ret = i + 1;
            return ret;
        }
    }
    return ret;
}

int main() {
    ifstream f {"day13.in"};
    string s;
    ll ans = 0;
    vector<vector<char>> grid;

    while (getline(f,s)) {
        if (s == "") {
            ans += find(grid);
            grid.clear();
            continue;
        }
        vector<char> row;
        for (char ch: s) {
            row.push_back(ch);
        }
        grid.push_back(row);
    }

    ans += find(grid);    
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

vector<int> splitInt(string s, char ch) {
    stringstream ss(s);
    vector<int> vec;

    for (int i; ss >> i;) {
        vec.push_back(i);
        if (ss.peek() == ch) {
            ss.ignore();
        }
    }
    return vec;
}
