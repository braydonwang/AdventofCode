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
set<char> maybe = {'|','-','L','J','7','F'};

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

    if (num == -1) {
        vis[r][c] = false;
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
    vector<vector<int>> comp(row, vector<int>(col));

    vis[sr][sc] = true;
    dfs(sr + 1, sc, 1, 1, vis);
    dfs(sr, sc + 1, 4, 1, vis);
    dfs(sr - 1, sc, 3, 1, vis);
    dfs(sr, sc - 1, 2, 1, vis);

    vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};
    for (int i = 0; i < 4; i++) {
        int nr = sr + dir[i][0], nc = sc + dir[i][1];
        if (nr < 0 || nr >= row || nc < 0 || nc >= col || !vis[nr][nc]) continue;
        if (i == 0) {
            maybe.erase('|'); maybe.erase('J'); maybe.erase('7');
        } else if (i == 1) {
            maybe.erase('|'); maybe.erase('L'); maybe.erase('F');
        } else if (i == 2) {
            maybe.erase('-'); maybe.erase('L'); maybe.erase('J');
        } else {
            maybe.erase('-'); maybe.erase('7'); maybe.erase('F');
        }
    }

    for (char ch: maybe) {
        grid[sr][sc] = ch;
    }

    int ans = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (!vis[i][j]) {
                int ind = j - 1, passes = 0, status = 0;
                // either | or F---J or L--7
                while (ind >= 0) {
                    if (!vis[i][ind]) {
                        ind--; continue;
                    }
                    if (grid[i][ind] == '|') {
                        passes++;
                        status = 0;
                    } else if (grid[i][ind] == 'J') {
                        status = 1;
                    } else if (grid[i][ind] == '7') {
                        status = 2;
                    } else if (grid[i][ind] == 'F') {
                        if (status == 1) {
                            passes++;
                        }
                        status = 0;
                    } else if (grid[i][ind] == 'L') {
                        if (status == 2) {
                            passes++;
                        }
                        status = 0;
                    }
                    ind--;
                }
                if (passes % 2 != 0) ans++;
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
