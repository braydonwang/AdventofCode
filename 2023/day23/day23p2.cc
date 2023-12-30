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
vector<string> splitStr(string s, char ch);

int r = 0, c = 0;
int start = 0, finish = 0;
vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};
map<pair<int,int>,map<pair<int,int>,int>> adj;

int dfs(int sr, int sc, vector<vector<bool>> &vis) {
    if (sr == r - 1 && sc == finish) {
        return 0;
    }
    int mx = -1;
    vis[sr][sc] = true;
    for (auto it: adj[{sr,sc}]) {
        if (vis[it.first.first][it.first.second]) continue;
        int num = dfs(it.first.first,it.first.second,vis);
        if (num != -1) {
            mx = max(mx,num + it.second);
        }
    }
    vis[sr][sc] = false;

    return mx;
}

int main() {
    ifstream f {"day23.in"};
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
    start = 0; finish = 0;
    for (int i = 0; i < c; i++) {
        if (grid[0][i] == '.') start = i;
        if (grid[r-1][i] == '.') finish = i;
    }

    vector<pair<int,int>> points;
    points.push_back({0,start}); points.push_back({r-1,finish});
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == '#') continue;
            int neighbours = 0;
            for (int k = 0; k < 4; k++) {
                int nr = i + dir[k][0], nc = j + dir[k][1];
                if (nr >= 0 && nr < r && nc >= 0 && nc < c && grid[nr][nc] != '#') {
                    neighbours++;
                }
            }
            if (neighbours >= 3) {
                points.push_back({i,j});
            }
        }
    }

    for (pair<int,int> p: points) {
        int sr = p.first, sc = p.second;
        queue<vector<int>> q;
        vector<vector<bool>> vis(r,vector<bool>(c));
        q.push({sr,sc,0}); vis[sr][sc] = true;

        while (!q.empty()) {
            vector<int> cur = q.front(); q.pop();
            pair<int,int> curP = make_pair(cur[0],cur[1]);
            if (find(points.begin(),points.end(),curP) != points.end() && cur[2] != 0) {
                adj[p][curP] = cur[2];
                continue;
            }
            for (int k = 0; k < 4; k++) {
                int nr = cur[0] + dir[k][0], nc = cur[1] + dir[k][1];
                if (nr >= 0 && nr < r && nc >= 0 && nc < c && grid[nr][nc] != '#' && !vis[nr][nc]) {
                    q.push({nr,nc,cur[2]+1});
                    vis[nr][nc] = true;
                }
            }
        }
    }

    vector<vector<bool>> vis(r,vector<bool>(c));
    cout << dfs(0,start,vis) << endl;
    
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

vector<string> splitStr(string s, char ch) {
    stringstream ss(s);
    vector<string> vec;
    while (ss.good()) {
        string str;
        getline(ss,str,ch);
        vec.push_back(str);
    }
    return vec;
}
