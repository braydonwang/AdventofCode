#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
using namespace std;

bool check(int hx, int hy, int tx, int ty) {
    vector<vector<int>> dir = {{0,0},{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};
    for (int i = 0; i < 9; i++) {
        int newx = hx + dir[i][0];
        int newy = hy + dir[i][1];
        if (newx == tx && newy == ty) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream f {"day9.in"};
    string s;

    int hx = 0, hy = 0, tx = 0, ty = 0;
    set<pair<int,int>> set;
    set.insert({tx,ty});

    while (f >> s) {
        int num;
        f >> num;
        while (num-- > 0) {
            int newx = hx, newy = hy;
            if (s == "L") {
                newx--;
            } else if (s == "R") {
                newx++;
            } else if (s == "D") {
                newy--;
            } else {
                newy++;
            }
            if (!check(newx,newy,tx,ty)) {
                tx = hx;
                ty = hy;
                set.insert({tx,ty});
            }
            hx = newx;
            hy = newy;
        }
    }

    cout << set.size() << endl;
    return 0;
}
