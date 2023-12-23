#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <queue>
using namespace std;

int main() {
    ifstream f {"day12.in"};
    string s;
    int ans = 0;
    vector<vector<char>> grid;
    vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};

    int sr = 0, sc = 0, er = 0, ec = 0;
    int row = 0, col = 0;

    while (f >> s) {
        vector<char> gridrow;
        col = 0;
        for (char ch: s) {
            if (ch == 'S') {
                sr = row; sc = col;
                gridrow.push_back('a');
                continue;
            } else if (ch == 'E') {
                er = row; ec = col;
                gridrow.push_back('z');
                continue;
            }
            gridrow.push_back(ch);
            col++;
        }
        grid.push_back(gridrow);
        row++;
    }
    int dis[row][col];
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            dis[i][j] = 1e9;
        }
    }

    dis[sr][sc] = 0;

    queue<pair<int,int>> q;
    q.push({sr,sc});
    while (!q.empty()) {
        int r = q.front().first, c = q.front().second; q.pop();
        for (int i = 0; i < 4; i++) {
            int newr = r + dir[i][0], newc = c + dir[i][1];
            if (newr >= 0 && newr < row && newc >= 0 && newc < col && grid[r][c] + 1 >= grid[newr][newc] && dis[newr][newc] > dis[r][c] + 1) {
                dis[newr][newc] = dis[r][c] + 1;
                q.push({newr,newc});
            }
        }
    }

    // for (int i = 0; i < row; i++) {
    //     for (int j = 0; j < col; j++) {
    //         cout << dis[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << dis[er][ec] << endl;

    return 0;
}
