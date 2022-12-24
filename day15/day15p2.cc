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

struct Pos {
    int sx;
    int sy;
    int bx;
    int by;
    Pos(int sx, int sy, int bx, int by): sx{sx}, sy{sy}, bx{bx}, by{by} {}
};

int main() {
    ifstream f {"day15.in"};
    string s;

    vector<Pos> vec;

    while (getline(f,s)) {
       istringstream iss{s};
       iss >> s; iss >> s; iss >> s;
       int sx = stoi(s.substr(2,s.length()-3));
       iss >> s;
       int sy = stoi(s.substr(2,s.length()-3));
       iss >> s; iss >> s; iss >> s; iss >> s; iss >> s;
       int bx = stoi(s.substr(2,s.length()-3));
       iss >> s;
       int by = stoi(s.substr(2,s.length()-2));

       vec.push_back({sx,sy,bx,by});
    }

    for (int row = 0; row <= 4000000; row++) {
        vector<pair<int,int>> intervals;
        for (Pos p: vec) {
            int dis = abs(p.sx-p.bx) + abs(p.sy-p.by);
            int diff = dis - abs(p.sy-row);

            if (diff >= 0) {
                intervals.push_back({p.sx-diff,p.sx+diff});
            }
            sort(intervals.begin(),intervals.end());
        }
        int x = 0;
        for (auto p: intervals) {
            if (x < p.first) {
                cout << (long)x * 4000000 + (long)row << endl;
                return 0;
            }
            x = max(x,p.second+1);
        }
    }

    return 0;
}
