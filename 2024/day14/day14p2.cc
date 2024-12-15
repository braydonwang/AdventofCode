#include <bits/stdc++.h>

using ll = long long;

const vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};
vector<string> split(string s, char delim);

void printGrid(int r, int c, vector<vector<int>> &grid) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << (grid[i][j] == 0 ? '.' : '#');
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    ifstream f {"day14.in"};
    string s;
    int r = 103, c = 101;
    ll tl = 0, tr = 0, bl = 0, br = 0;

    vector<vector<int>> points;
    
    while (getline(f, s)) {
        vector<string> vec = split(s, ' ');
        vector<string> coords = split(vec[0].substr(2), ',');
        vector<string> vels = split(vec[1].substr(2), ',');

        int row = stoi(coords[1]), col = stoi(coords[0]);
        int vr = stoi(vels[1]), vc = stoi(vels[0]);

        points.push_back({row, col, vr, vc});
    }

    int iters = 1;
    while (iters < 11000) {
        vector<vector<int>> grid(r, vector<int>(c));

        for (vector<int> &p: points) {
            p[0] = ((p[0] + p[2]) % r + r) % r;
            p[1] = ((p[1] + p[3]) % c + c) % c;
            grid[p[0]][p[1]]++;
        }
        
        int cluster = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (grid[i][j] > 0) {
                    for (int k = 0; k < 4; k++) {
                        int nr = i + dir[k][0], nc = j + dir[k][1];
                        if (nr >= 0 && nr < r && nc >= 0 && nc < c) {
                            cluster += grid[nr][nc];
                        }
                    }
                }
            }
        }

        if (cluster >= 500) {
            printGrid(r, c, grid);
            break;
        }
        iters++;
    }

    cout << iters << endl;
}

vector<string> split(string s, char delim) {
    int ind = 0;
    string acc = "";
    vector<string> vec;

    while (ind < s.length()) {
        if (s[ind] == delim) {
            vec.push_back(acc);
            acc = "";
        } else {
            acc += s[ind];
        }
        ind++;
    }
    vec.push_back(acc);

    return vec;
}
