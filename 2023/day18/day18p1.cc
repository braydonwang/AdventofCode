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

unordered_map<string,pair<int,int>> dir = {{"U", {-1,0}}, {"D", {1,0}}, {"L", {0,-1}}, {"R", {0,1}}};  

int main() {
    ifstream f {"day18.in"};
    string s;
    vector<pair<int,int>> points = {{0,0}};
    pair<int,int> cur = {0,0};
    int boundary = 0;

    while (getline(f,s)) {
        vector<string> vec = split(s);
        string d = vec[0];
        int num = stoi(vec[1]);
        boundary += num;
        int dr = dir[d].first, dc = dir[d].second;

        cur = {cur.first + dr * num, cur.second + dc * num};
        points.push_back(cur);
    }

    int sum = 0, sz = points.size();
    for (int i = 0; i < sz; i++) {
        sum += points[i].first * (points[(i-1+sz)%sz].second - points[(i+1)%sz].second);
    }
    int area = abs(sum) / 2;
    int interior = area - boundary/2 + 1;

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
