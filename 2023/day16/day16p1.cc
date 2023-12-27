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

//                           R      L     D      U
vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};
int r = 0, c = 0;

void dfs(int row, int col, vector<vector<int>> &vis, vector<vector<char>> &grid, int d) {
    if (row < 0 || row >= r || col < 0 || col >= c || vis[row][col] == d) return;
    vis[row][col] = d;

    int newDir = d, newDir2 = -1;
    if (grid[row][col] == '/') {
        newDir = 3 - d;
    } else if (grid[row][col] == '\\') {
        newDir = (d + 2) % 4;
    } else if (grid[row][col] == '|' && d <= 1) {
        newDir = 2; newDir2 = 3;
    } else if (grid[row][col] == '-' && d >= 2) {
        newDir = 0; newDir2 = 1;
    }

    int newRow = row + dir[newDir][0], newCol = col + dir[newDir][1];
    dfs(newRow,newCol,vis,grid,newDir);
    if (newDir2 != -1) {
        int newRow2 = row + dir[newDir2][0], newCol2 = col + dir[newDir2][1];
        dfs(newRow2,newCol2,vis,grid,newDir2);
    }
}

int main() {
    ifstream f {"day16.in"};
    string s;
    vector<vector<char>> grid;

    while (getline(f,s)) {
        vector<char> row;
        for (char ch: s) {
            row.push_back(ch);
        }
        grid.push_back(row);
    }

    r = grid.size(); c = grid[0].size();
    vector<vector<int>> vis(r, vector<int>(c, -1));
    dfs(0,0,vis,grid,0);

    int ans = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (vis[i][j] != -1) ans++;
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
