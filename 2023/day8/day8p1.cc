#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <unordered_map>
#include <regex>
#include <string>

using namespace std;
#define ll long long

vector<string> split(string s);

int main() {
    ifstream f {"day8.in"};
    string s;
    getline(f,s);
    string seq = s;
    unordered_map<string,pair<string,string>> edges;
    int steps = 0;
    getline(f,s);

    while (getline(f,s)) {
        vector<string> vec = split(s);
        string node = vec[0], l = vec[2].substr(1,vec[2].length()-2), r = vec[3].substr(0,vec[3].length()-1);
        edges[node] = {l,r};
    }

    string cur = "AAA";
    int ind = 0;
    while (cur != "ZZZ") {
        if (seq[ind] == 'L') {
            cur = edges[cur].first;
        } else {
            cur = edges[cur].second;
        }
        ind = (ind + 1) % seq.length();
        steps++;
    }
    
    cout << steps << endl;

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
