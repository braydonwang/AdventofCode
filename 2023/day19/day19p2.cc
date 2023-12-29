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
vector<string> splitStr(string s, char ch);

ll ans = 0;
unordered_map<string,vector<string>> flows;
unordered_map<char,int> part = {{'x',0},{'m',1},{'a',2},{'s',3}};

void check(vector<pair<int,int>> ranges, string name) {
    if (name == "R") return;
    if (name == "A") {
        ll sum = 1;
        for (int i = 0; i < 4; i++) {
            if (ranges[i].second >= ranges[i].first) {
                sum *= ranges[i].second - ranges[i].first + 1;
            } else {
                sum = 0;
            }
        }
        ans += sum;
        return;
    }

    vector<string> conds = flows[name];
    for (string str: conds) {
        if (str[1] == '>' || str[1] == '<') {
            vector<string> vec = splitStr(str, ':');
            int p = part[str[0]];
            int num = stoi(vec[0].substr(2,vec[0].length()-2));
            if (str[1] == '>') {
                int temp = ranges[p].first;
                ranges[p].first = num + 1;
                check(ranges, vec[1]);
                ranges[p].first = temp;
                ranges[p].second = num;
            } else {
                int temp = ranges[p].second;
                ranges[p].second = num - 1;
                check(ranges,vec[1]);
                ranges[p].second = temp;
                ranges[p].first = num;
            }
        } else {
            return check(ranges, str);
        }
    }
}

int main() {
    ifstream f {"day19.in"};
    string s;
    bool getRatings = false;

    while (getline(f,s)) {
        if (s == "") {
            getRatings = true;
            continue;
        }
        if (getRatings) {
           continue;
        } else {
            vector<string> temp = splitStr(s.substr(0,s.length()-1), '{');
            string name = temp[0];
            vector<string> conds = splitStr(temp[1],',');
            flows[name] = conds;
        }
    }

    vector<pair<int,int>> ranges(4,{1,4000});
    check(ranges,"in");
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
