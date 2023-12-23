#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <regex>

using namespace std;
vector<string> split(string s);

int parse(vector<vector<char>> &grid, int i, int j) {
    int num = 0;
    while (j < grid[i].size() && grid[i][j] >= '0' && grid[i][j] <= '9') {
        num = num * 10 + grid[i][j] - '0';
        j++;
    }
    return num;
}

int main() {
    ifstream f {"day3.in"};
    string s;
    vector<vector<char>> grid;
    vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0},{1,1},{-1,-1},{1,-1},{-1,1}};
    int r = 0, c = 0;
    long sum = 0;

    while (getline(f,s)) {
        r = s.length();
        c++;
        vector<char> row;
        for (int i = 0; i < s.length(); i++) {
            row.push_back(s[i]);
        }
        grid.push_back(row);
    }

    vector<vector<bool>> vis(r, vector<bool>(c));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == '*') {
                vector<int> adj;
                for (int k = 0; k < 8; k++) {
                    int newR = i + dir[k][0], newC = j + dir[k][1];
                    if (newR >= 0 && newR < r && newC >= 0 && newC < c && grid[newR][newC] >= '0' && grid[newR][newC] <= '9') {
                        while (newC >= 0 && grid[newR][newC] >= '0' && grid[newR][newC] <= '9') {
                            newC--;
                        }
                        newC++;
                        if (!vis[newR][newC]) {
                            vis[newR][newC] = true;
                            adj.push_back(parse(grid,newR,newC));
                            if (adj.size() > 2) {
                                break;
                            }
                        }
                    }
                }
                if (adj.size() == 2) {
                    sum += adj[0] * adj[1];
                }
            }
        }
    }

    cout << sum << endl;
    
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
