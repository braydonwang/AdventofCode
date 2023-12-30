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
vector<vector<char>> grid;

struct Pos {
    int row;
    int col;
    int dis;
    Pos(int row, int col, int dis): row{row}, col{col}, dis{dis} {}
};

ll solve(int sr, int sc, int dis) {
    queue<Pos> q;
    set<pair<int,int>> locations;
    vector<vector<bool>> vis(r,vector<bool>(c));
    q.push({sr,sc,dis});
    vis[sr][sc] = true;

    while (!q.empty()) {
        Pos cur = q.front(); q.pop();
        if (cur.dis % 2 == 0) {
            locations.insert({cur.row,cur.col});
        }
        if (cur.dis == 0) {
            continue;
        }
        for (int k = 0; k < 4; k++) {
            int newRow = cur.row + dir[k][0], newCol = cur.col + dir[k][1];
            if (newRow >= 0 && newRow < r && newCol >= 0 && newCol < c && grid[newRow][newCol] != '#' && !vis[newRow][newCol]) {
                q.push({newRow,newCol,cur.dis-1});
                vis[newRow][newCol] = true;
            }
        }
    }
    
    return locations.size();
}

int main() {
    ifstream f {"day21.in"};
    string s;
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

    ll steps = 26501365;
    ll size = r;
    ll gridWidth = steps / size - 1;
    ll odd = (gridWidth / 2 * 2 + 1) * (gridWidth / 2 * 2 + 1);
    ll even = ((gridWidth + 1) / 2 * 2) * ((gridWidth + 1) / 2 * 2);

    ll oddPoints = solve(sr,sc,2*size + 1);
    ll evenPoints = solve(sr,sc,2*size);

    ll cornerTop = solve(size-1,sc,size-1);
    ll cornerBot = solve(0,sc,size-1);
    ll cornerLeft = solve(sr,size-1,size-1);
    ll cornerRight = solve(sr,0,size-1);

    ll smallTR = solve(size-1,0,size/2-1);
    ll smallTL = solve(size-1,size-1,size/2-1);
    ll smallBL = solve(0,size-1,size/2-1);
    ll smallBR = solve(0,0,size/2-1);

    ll largeTR = solve(size-1,0,3*size/2-1);
    ll largeTL = solve(size-1,size-1,3*size/2-1);
    ll largeBL = solve(0,size-1,3*size/2-1);
    ll largeBR = solve(0,0,3*size/2-1);
    
    ll ans = (odd * oddPoints) + (even * evenPoints)
           + cornerTop + cornerBot + cornerLeft + cornerRight
           + (gridWidth + 1) * (smallTR + smallTL + smallBL + smallBR)
           + gridWidth * (largeTR + largeTL + largeBL + largeBR);

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
