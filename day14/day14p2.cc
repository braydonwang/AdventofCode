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

pair<int,int> parse(string s) {
    int ind = 0;
    while (s[ind] != ',') {
        ind++;
    }
    return {stoi(s.substr(0,ind)),stoi(s.substr(ind+1,s.length()-ind-1))};
}

int main() {
    ifstream f {"day14.in"};
    string s;
    int ans = 0;

    set<pair<int,int>> set;
    int maxy = 0;

    while (getline(f,s)) {
       istringstream iss{s};
       string str;

       pair<int,int> pre = {-1,-1};

       while (iss >> str) {
           if (str[0] != '-') {
            pair<int,int> p = parse(str);
            if (pre.first == -1) {
                pre = p;
            } else {
                if (pre.first == p.first) {
                    int a = min(pre.second,p.second), b = max(pre.second,p.second);
                    for (int i = a; i <= b; i++) {
                        set.insert({pre.first,i});
                        maxy = max(maxy,i);
                    }
                } else {
                    int a = min(pre.first,p.first), b = max(pre.first,p.first);
                    for (int i = a; i <= b; i++) {
                        set.insert({i,pre.second});
                        maxy = max(maxy,pre.second);
                    }
                }
            }
            pre = p;
           }
        }
    }

    int x = 500, y = 0;

    while (set.count({500,0}) == 0) {
        if (y == maxy + 1) {
            ans++;
            set.insert({x,y});
            x = 500; y = 0;
        } else if (set.count({x,y+1}) == 0) {
            y++;
        } else if (set.count({x-1,y+1}) == 0) {
            x--; y++;
        } else if (set.count({x+1,y+1}) == 0) {
            x++; y++;
        } else {
            ans++;
            set.insert({x,y});
            x = 500; y = 0;
        }
    }

    cout << ans << endl;

    return 0;
}
