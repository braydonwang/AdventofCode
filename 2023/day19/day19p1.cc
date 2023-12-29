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

unordered_map<string,vector<string>> flows;
unordered_map<char,int> part = {{'x',0},{'m',1},{'a',2},{'s',3}};

bool check(vector<int> ratings, string name) {
    if (name == "A") return true;
    if (name == "R") return false;
    vector<string> conds = flows[name];
    for (string str: conds) {
        if (str[1] == '>' || str[1] == '<') {
            vector<string> vec = splitStr(str, ':');
            int amount = ratings[part[str[0]]], num = stoi(vec[0].substr(2,vec[0].length()-2));
            if (str[1] == '>' && amount > num) {
                return check(ratings, vec[1]);
            } else if (str[1] == '<' && amount < num) {
                return check(ratings, vec[1]);
            }
        } else {
            return check(ratings, str);
        }
    }
    return false;
}

int main() {
    ifstream f {"day19.in"};
    string s;
    bool getRatings = false;
    ll ans = 0;

    while (getline(f,s)) {
        if (s == "") {
            getRatings = true;
            continue;
        }
        if (getRatings) {
            s = s.substr(1,s.length()-2);
            vector<string> temp = splitStr(s, ',');
            vector<int> ratings;
            ll sum = 0;
            for (int i = 0; i < 4; i++) {
                int num = stoi(temp[i].substr(2,temp[i].length()-2));
                ratings.push_back(num);
                sum += num;
            }
            if (check(ratings, "in")) {
                ans += sum;
            }
        } else {
            vector<string> temp = splitStr(s.substr(0,s.length()-1), '{');
            string name = temp[0];
            vector<string> conds = splitStr(temp[1],',');
            flows[name] = conds;
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
