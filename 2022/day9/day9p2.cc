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

    int hx = 0, hy = 0;
    vector<pair<int,int>> vec;
    for (int i = 0; i < 9; i++) {
        vec.push_back({0,0});
    }
    set<pair<int,int>> set;
    set.insert({0,0});

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
            if (!check(newx,newy,vec[0].first,vec[0].second)) {
                vec[0] = {hx,hy};
                for (int i = 1; i < 9; i++) {
                    if (!check(vec[i-1].first,vec[i-1].second,vec[i].first,vec[i].second)) {
                        int x = vec[i-1].first, y = vec[i-1].second;
                        int cx = vec[i].first, cy = vec[i].second;
                        if (x > cx) {
                            vec[i].first++;
                        } else if (x < cx) {
                            vec[i].first--;
                        }
                        if (y > cy) {
                            vec[i].second++;
                        } else if (y < cy) {
                            vec[i].second--;
                        }
                    }
                }
                set.insert(vec[8]);
            }
            hx = newx;
            hy = newy;
        }
    }

    cout << set.size() << endl;
    return 0;
}
