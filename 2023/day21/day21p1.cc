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
vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};

struct Pos {
    int row;
    int col;
    int dis;
    Pos(int row, int col, int dis): row{row}, col{col}, dis{dis} {}
};

int main() {
    ifstream f {"day21.in"};
    string s;
    vector<vector<char>> grid;
    set<pair<int,int>> locations;
    r = 0; c = 0;
    int sr = 0, sc = 0;

    while (getline(f,s)) {
        vector<char> row;
        for (int i = 0; i < s.length(); i++) {
            row.push_back(s[i]);
            if (s[i] == 'S') {
                sr = r; sc = i;
            }
        }
        grid.push_back(row);
        r++;
    }
    c = grid[0].size();
    
    queue<Pos> q;
    vector<vector<bool>> vis(r,vector<bool>(c));
    q.push({sr,sc,0});
    vis[sr][sc] = true;

    while (!q.empty()) {
        Pos cur = q.front(); q.pop();
        if (cur.dis % 2 == 0) {
            locations.insert({cur.row,cur.col});
        }
        if (cur.dis == 64) {
            continue;
        }
        for (int k = 0; k < 4; k++) {
            int newRow = cur.row + dir[k][0], newCol = cur.col + dir[k][1];
            if (newRow >= 0 && newRow < r && newCol >= 0 && newCol < c && grid[newRow][newCol] == '.' && !vis[newRow][newCol]) {
                q.push({newRow,newCol,cur.dis+1});
                vis[newRow][newCol] = true;
            }
        }
    }
    
    cout << locations.size() << endl;
    
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
