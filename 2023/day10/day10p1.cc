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


int row = 0, col = 0;
vector<vector<char>> grid;

int dfs(int r, int c, int dir, int dis, vector<vector<bool>> &vis) {
    if (r < 0 || r >= row || c < 0 || c >= col || grid[r][c] == '.') {
        return -1;
    }

    if (vis[r][c]) {
        if (grid[r][c] == 'S') {
            return dis;
        }
        return -1;
    }
    // 1 = top, 2 = right, 3 = bottom, 4 = left
    vis[r][c] = true;
    int num = -1;
    if (dir == 1) {
        if (grid[r][c] == '|') {
            num = dfs(r+1, c, 1, dis+1, vis);
        } else if (grid[r][c] == 'L') {
            num = dfs(r,c+1,4, dis+1, vis);
        } else if (grid[r][c] == 'J') {
            num = dfs(r,c-1,2,dis+1,vis);
        }
    } else if (dir == 2) {
        if (grid[r][c] == '-') {
            num = dfs(r,c-1,2,dis+1,vis);
        } else if (grid[r][c] == 'L') {
            num = dfs(r-1,c,3,dis+1,vis);
        } else if (grid[r][c] == 'F') {
            num = dfs(r+1,c,1,dis+1,vis);
        }
    } else if (dir == 3) {
        if (grid[r][c] == '|') {
            num = dfs(r-1,c,3,dis+1,vis);
        } else if (grid[r][c] == '7') {
            num = dfs(r,c-1,2,dis+1,vis);
        } else if (grid[r][c] == 'F') {
            num = dfs(r,c+1,4,dis+1,vis);
        }
    } else {
        if (grid[r][c] == '-') {
            num = dfs(r,c+1,4,dis+1,vis);
        } else if (grid[r][c] == 'J') {
            num = dfs(r-1,c,3,dis+1,vis);
        } else if (grid[r][c] == '7') {
            num = dfs(r+1,c,1,dis+1,vis);
        }
    }

    return num;
}

int main() {
    ifstream f {"day10.in"};
    string s;
    int sr = 0, sc = 0;

    while (getline(f,s)) {
        vector<char> vec;
        for (int i = 0; i < s.length(); i++) {
            vec.push_back(s[i]);
            if (s[i] == 'S') {
                sr = grid.size(); sc = i;
            }
        }
        grid.push_back(vec);
    }

    row = grid.size(); col = grid[0].size();
    vector<vector<bool>> vis(row, vector<bool>(col));
    vis[sr][sc] = true;
    int ans = max({dfs(sr + 1, sc, 1, 1, vis), dfs(sr, sc + 1, 4, 1, vis), dfs(sr - 1, sc, 3, 1, vis), dfs(sr, sc - 1, 2, 1, vis)});
    cout << ans / 2 << endl;
    
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
