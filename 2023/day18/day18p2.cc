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

vector<string> split(string s);
vector<int> splitInt(string s, char ch);

vector<vector<int>> dir = {{0,1},{1,0},{0,-1},{-1,0}};  

int main() {
    ifstream f {"day18.in"};
    string s;
    vector<pair<ll,ll>> points = {{0,0}};
    pair<ll,ll> cur = {0,0};
    int boundary = 0;

    while (getline(f,s)) {
        vector<string> vec = split(s);
        string hex = vec[2];
        ll num = 0;
        for (int i = 2; i < 7; i++) {
            num *= 16;
            if (hex[i] >= '0' && hex[i] <= '9') {
                num += hex[i] - '0';
            } else {
                num += hex[i] - 'a' + 10;
            }
        }
        int d = hex[7] - '0';
        boundary += num;
        ll dr = dir[d][0], dc = dir[d][1];

        cur = {cur.first + dr * num, cur.second + dc * num};
        points.push_back(cur);
    }

    ll sum = 0, sz = points.size();
    for (int i = 0; i < sz; i++) {
        sum += points[i].first * (points[(i-1+sz)%sz].second - points[(i+1)%sz].second);
    }
    ll area = abs(sum) / 2;
    ll interior = area - boundary/2 + 1;

    cout << interior + boundary << endl;
    
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

vector<int> splitInt(string s, char ch) {
    stringstream ss(s);
    vector<int> vec;

    for (int i; ss >> i;) {
        vec.push_back(i);
        if (ss.peek() == ch) {
            ss.ignore();
        }
    }
    return vec;
}
