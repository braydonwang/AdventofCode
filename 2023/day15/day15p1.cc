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

int main() {
    ifstream f {"day15.in"};
    string s;
    ll ans = 0;

    getline(f,s);
    vector<string> steps = splitStr(s, ',');
    for (string str: steps) {
        int cur = 0;
        for (char ch: str) {
            cur = (cur + ch) * 17 % 256;
        }
        ans += cur;
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
        getline(ss,str,',');
        vec.push_back(str);
    }
    return vec;
}
