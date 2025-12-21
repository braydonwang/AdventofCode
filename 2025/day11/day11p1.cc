#include <bits/stdc++.h>
using ll = long long;

vector<string> split(string s, char delim = ' ');

int main() {
    ifstream f {"day11.in"};
    string s;
    unordered_map<string, vector<string>> adj;

    while (getline(f, s)) {
        if (s.empty()) break;
        vector<string> v = split(s);
        v[0].pop_back();
        vector<string> n(v.begin()+1, v.end());
        adj[v[0]] = n;
    }

    ll ans = 0;
    queue<string> q;
    q.push("you");

    while (!q.empty()) {
        string cur = q.front(); q.pop();
        if (cur == "out") {
            ans++;
            continue;
        }

        for (string nxt: adj[cur]) {
            q.push(nxt);
        }
    }

    cout << ans << endl;
}

vector<string> split(string s, char delim) {
    vector<string> vec;
    string acc = "";

    for (char ch: s) {
        if (ch == delim) {
            vec.push_back(acc);
            acc = "";
        } else {
            acc += ch;
        }
    }

    if (!acc.empty()) vec.push_back(acc);
    return vec;
}
