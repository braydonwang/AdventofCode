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
    ifstream f {"day20.in"};
    string s;
    ll ans = 0, low = 0, high = 0;
    unordered_map<string,vector<string>> adj;
    unordered_map<string,vector<string>> rev;
    unordered_map<string,bool> type;
    unordered_map<string,unordered_map<string,bool>> conj;
    unordered_map<string,bool> flip;

    while (getline(f,s)) {
        vector<string> vec = splitStr(s, '-');
        string source = vec[0].substr(0,vec[0].length()-1);
        vector<string> dest = splitStr(vec[1].substr(2,vec[1].length()-2),',');
        for (string &d: dest) {
            if (d[0] == ' ') d = d.substr(1,d.length()-1);
        }
        bool tp = false;
        if (source[0] == '&') tp = true;
        if (source != "broadcaster") source = source.substr(1,source.length()-1);

        adj[source] = dest;
        type[source] = tp;
        for (string d: dest) {
            if (rev.find(d) == rev.end()) {
                rev[d] = {};
            }
            rev[d].push_back(source);
        }
    }

    for (auto it: type) {
        if (it.second) {
            for (string mod: rev[it.first]) {
                conj[it.first][mod] = false;
            }
        } else {
            flip[it.first] = false;
        }
    }
    adj["button"] = {"broadcaster"};

    for (int z = 0; z < 1000; z++) {
        queue<pair<string,bool>> q;
        q.push({"button", false});
        while (!q.empty()) {
            pair<string,bool> p = q.front(); q.pop();
            string cur = p.first;
            bool pulse = p.second;
            bool send = pulse;
            
            if (cur == "button" || cur == "broadcaster") {
                send = pulse;
            } else if (!type[cur]) {
                if (pulse) continue;
                flip[cur] = !flip[cur];
                send = flip[cur];
            } else {
                bool allHigh = true;
                for (string mod: rev[cur]) {
                    if (!conj[cur][mod]) {
                        allHigh = false;
                        break;
                    }
                }
                send = !allHigh;
            }

            if (send) {
                high += adj[cur].size();
            } else {
                low += adj[cur].size();
            }

            for (string mod: adj[cur]) {
                if (type[mod]) {
                    conj[mod][cur] = send;
                }
                q.push({mod,send});
            }
        }
    }
    
    ans = low * high;
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
