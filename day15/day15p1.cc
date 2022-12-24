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
    ifstream f {"day15.in"};
    string s;
    int row = 2000000;

    set<int> beacon;
    set<int> set;

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

       if (by == row) {
        beacon.insert(bx);
       }
       
       int dis = abs(sx-bx) + abs(sy-by);
       int diff = dis - abs(sy-row);

       if (diff >= 0) {
        for (int i = sx - diff; i <= sx + diff; i++) {
            set.insert(i);
        }
       }
    }

    cout << set.size() - beacon.size() << endl;

    return 0;
}
