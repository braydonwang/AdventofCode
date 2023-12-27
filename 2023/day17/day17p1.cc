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

int r = 0, c = 0;
//                           R     D      L      U
vector<vector<int>> dir = {{0,1},{1,0},{0,-1},{-1,0}};

struct Block {
    int row;
    int col;
    int d;
    int count;

    Block(int row, int col, int d, int count): row{row}, col{col}, d{d}, count{count} {}
};

int main() {
    ifstream f {"day17.in"};
    string s;
    vector<vector<int>> grid;
    int ans = 1e9;

    while (getline(f,s)) {
        vector<int> row;
        for (char ch: s) {
            row.push_back(ch - '0');
        }
        grid.push_back(row);
    }

    r = grid.size(); c = grid[0].size();
    vector<vector<vector<vector<int>>>> dp(r, vector<vector<vector<int>>>(c, vector<vector<int>>(4, vector<int>(4, 1e9))));
    dp[0][0][0][0] = 0; dp[0][0][2][0] = 0;
    queue<Block> q;
    q.push({0,0,0,0}); q.push({0,0,2,0});

    while (!q.empty()) {
       Block cur = q.front(); q.pop();
       int dis = dp[cur.row][cur.col][cur.d][cur.count];
       if (cur.row == r - 1 && cur.col == c - 1) {
        ans = min(ans,dis);
        continue;
       }
       for (int k = 0; k < 4; k++) {
        if (cur.d == k && cur.count == 3) continue;
        if (cur.d % 2 == k % 2 && k != cur.d) continue;
        int newRow = cur.row + dir[k][0], newCol = cur.col + dir[k][1];
        int count = 1;
        if (k == cur.d) count = cur.count + 1;
        if (newRow >= 0 && newRow < r && newCol >= 0 && newCol < c && dis + grid[newRow][newCol] < dp[newRow][newCol][k][count]) {
            dp[newRow][newCol][k][count] = dis + grid[newRow][newCol];
            q.push({newRow,newCol,k,count});
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
