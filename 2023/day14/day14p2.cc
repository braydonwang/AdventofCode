#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <unordered_map>
#include <map>
#include <regex>
#include <string>

using namespace std;
#define ll long long

vector<string> split(string s);
vector<int> splitInt(string s, char ch);

vector<vector<char>> rotate(vector<vector<char>> &grid) {
    vector<vector<char>> newGrid;
    for (int i = 0; i < grid[0].size(); i++) {
        vector<char> row;
        for (int j = 0; j < grid.size(); j++) {
            row.push_back(grid[j][i]);
        }
        newGrid.push_back(row);
    }

    for (int i = 0; i < newGrid.size(); i++) {
        reverse(newGrid[i].begin(), newGrid[i].end());
    }

    return newGrid;
}

void move(vector<vector<char>> &grid) {
    int r = grid.size(), c = grid[0].size();

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            if (grid[j][i] == 'O') {
                int ind = j - 1;
                while (ind >= 0 && grid[ind][i] == '.') ind--;
                ind++;
                swap(grid[ind][i], grid[j][i]);
            }
        }
    }
}

void cycle(vector<vector<char>> &grid) {
    for (int k = 0; k < 4; k++) {
        move(grid);
        grid = rotate(grid);
    }
}

int main() {
    ifstream f {"day14.in"};
    string s;
    vector<vector<char>> grid;
    ll ans = 0;

    while (getline(f,s)) {
        vector<char> row;
        for (char ch: s) {
            row.push_back(ch);
        }
        grid.push_back(row);
    }

    int count = 1000000000;
    map<vector<vector<char>>,int> seen;

    while (count > 0) {
        cycle(grid);
        count--;
        if (seen.find(grid) != seen.end()) {
            count %= seen[grid] - count;
        } else {
            seen[grid] = count;
        }
    }

    int r = grid.size(), c = grid[0].size();

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == 'O') {
                ans += r - i;
            }
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
