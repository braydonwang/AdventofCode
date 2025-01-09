#include <bits/stdc++.h>

using ll = long long;

const vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};

vector<string> split(string &s) {
    vector<string> ret;
    int ind = 0;
    string acc = "";

    while (ind < s.length()) {
        if (s[ind] == ' ') {
            ret.push_back(acc);
            acc = "";
        } else {
            acc += s[ind];
        }
        ind++;
    }

    ret.push_back(acc);
    return ret;
}

int main() {
    ifstream f {"day24.in"};
    string s;

    unordered_map<string, int> vals;
    unordered_map<string, int> in;
    unordered_map<string, vector<string>> adj;
    unordered_map<string, vector<string>> rev;
    set<string> zs;
    queue<string> seen;

    while (getline(f, s)) {
        if (s.empty()) break;
        vector<string> vec = split(s);
        string name = vec[0].substr(0, vec[0].length() - 1);
        int amt = stoi(vec[1]);
        vals[name] = amt;
        seen.push(name);
    }

    while (getline(f, s)) {
        vector<string> vec = split(s);
        string na = vec[0], op = vec[1], nb = vec[2], nc = vec[4];
        in[nc] = 2;
        adj[na].push_back(nc); adj[nb].push_back(nc);
        rev[nc] = {na, op, nb};
        if (nc[0] == 'z') {
            zs.insert(nc);
        }
    }

    while (!seen.empty()) {
        string cur = seen.front(); seen.pop();
        for (string nxt: adj[cur]) {
            in[nxt]--;
            if (in[nxt] == 0) {
                string a = rev[nxt][0], op = rev[nxt][1], b = rev[nxt][2];
                int val = 0;
                if (op == "AND") {
                    val = vals[a] & vals[b];
                } else if (op == "OR") {
                    val = vals[a] | vals[b];
                } else {
                    val = vals[a] ^ vals[b];
                }
                vals[nxt] = val;
                seen.push(nxt);
            }
        }
    }

    string ans = "";
    for (string z: zs) {
        ans += to_string(vals[z]);
    }
    reverse(ans.begin(), ans.end());

    cout << stoll(ans, nullptr, 2) << endl;
}
