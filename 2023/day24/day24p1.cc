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
#define ld long double

vector<string> split(string s);
vector<ll> splitInt(string s, char ch);
vector<string> splitStr(string s, char ch);

pair<ld,ld> intersect(vector<ll> s1, vector<ll> s2) {
    ll x1 = s1[0], y1 = s1[1], vx1 = s1[3], vy1 = s1[4];
    ll x2 = s2[0], y2 = s2[1], vx2 = s2[3], vy2 = s2[4];
    ld m1 = 1.0*vy1/vx1, m2 = 1.0*vy2/vx2;
    ld b1 = y1 - m1 * x1, b2 = y2 - m2 * x2;
    ld intersectX = (b2 - b1) / (m1 - m2);
    ld intersectY = m1 * intersectX + b1;
    return {intersectX, intersectY};
}

bool check(pair<ld,ld> pos, vector<ll> s) {
    ll x = s[0], y = s[1], vx = s[3], vy = s[4];
    if (vx > 0 && pos.first < x) return false;
    if (vx < 0 && pos.first > x) return false;
    if (vy > 0 && pos.second < y) return false;
    if (vy < 0 && pos.second > y) return false;
    return true;
}

int main() {
    ifstream f {"day24.in"};
    string s;
    vector<vector<ll>> stones;

    while (getline(f,s)) {
        vector<string> vec = splitStr(s,'@');
        vector<ll> pos = splitInt(vec[0],',');
        vector<ll> vel = splitInt(vec[1].substr(1,vec[1].length()-1),',');
        vector<ll> stone;
        for (ll num: pos) {
            stone.push_back(num);
        }
        for (ll num: vel) {
            stone.push_back(num);
        }
        stones.push_back(stone);
    }

    ll mintest = 200000000000000, maxtest = 400000000000000;
    int ans = 0;
    int sz = stones.size();
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < i; j++) {
            pair<ld,ld> pos = intersect(stones[i],stones[j]);
            if (pos.first >= mintest && pos.first <= maxtest && pos.second >= mintest && pos.second <= maxtest && check(pos,stones[i]) && check(pos,stones[j])) {
                ans++;
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

vector<ll> splitInt(string s, char ch) {
    stringstream ss(s);
    vector<ll> vec;

    for (ll i; ss >> i;) {
        vec.push_back(i);
        if (ss.peek() == ch) {
            ss.ignore();
        }
    }
    return vec;
}

vector<string> splitStr(string s, char ch) {
    stringstream ss(s);
    vector<string> vec;
    while (ss.good()) {
        string str;
        getline(ss,str,ch);
        vec.push_back(str);
    }
    return vec;
}
