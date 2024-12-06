#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <regex>

using ll = long long;

using namespace std;
vector<int> split(string s);

const string xmas = "XMAS";

bool valid(int r, int c, vector<vector<char>> &grid) {
    char tl = grid[r][c], tr = grid[r][c+2], bl = grid[r+2][c], br = grid[r+2][c+2];
    char mid = grid[r+1][c+1];
    if (mid != 'A') return false;

    bool gooda = (tl == 'M' && br == 'S') || (tl == 'S' && br == 'M');
    bool goodb = (tr == 'M' && bl == 'S') || (tr == 'S' && bl == 'M');
    return gooda && goodb;
}

int main() {
    ifstream f {"day4.in"};
    string s;
    vector<vector<char>> grid;

    while (getline(f,s)) {
        vector<char> row;
        for (char ch: s) {
            row.push_back(ch);
        }
        grid.push_back(row);
    }

    int r = grid.size(), c = grid[0].size(), sum = 0;

    for (int i = 0; i < r-2; i++) {
        for (int j = 0; j < c-2; j++) {
            if (valid(i, j, grid)) {
                sum++;
            }
        }
    }

    cout << sum << endl;
}

vector<int> split(string s) {
    stringstream ss(s);
    int x;
    vector<int> vec;

    while (ss >> x) {
        vec.push_back(x);
    }
    return vec;
}
