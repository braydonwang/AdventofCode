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

bool check(string node) {
    return node[node.length()-1] == 'Z';
}

ll gcd(ll a, ll b) {
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

int main() {
    ifstream f {"day8.in"};
    string s;
    getline(f,s);
    string seq = s;
    unordered_map<string,pair<string,string>> edges;
    ll steps = 1;
    vector<string> cur;
    getline(f,s);

    while (getline(f,s)) {
        vector<string> vec = split(s);
        string node = vec[0], l = vec[2].substr(1,vec[2].length()-2), r = vec[3].substr(0,vec[3].length()-1);
        if (node[node.length()-1] == 'A') {
            cur.push_back(node);
        }
        edges[node] = {l,r};
    }

    for (int i = 0; i < cur.size(); i++) {
        int ind = 0;
        string node = cur[i];
        while (!check(node)) {
            if (seq[ind] == 'L') {
                node = edges[node].first;
            } else {
                node = edges[node].second;
            }
            ind = (ind + 1) % seq.length();
        }

        ll count = 1;
        if (seq[ind] == 'L') {
            node = edges[node].first;
        } else {
            node = edges[node].second;
        }
        ind = (ind + 1) % seq.length();

        while (!check(node)) {
            if (seq[ind] == 'L') {
                node = edges[node].first;
            } else {
                node = edges[node].second;
            }
            ind = (ind + 1) % seq.length();
            count++;
        }
        steps = (steps * count) / gcd(steps, count);
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
