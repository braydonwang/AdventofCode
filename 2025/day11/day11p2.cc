#include <bits/stdc++.h>
using ll = long long;

vector<string> split(string s, char delim = ' ');

ll solve(string &cur, string &end, unordered_map<string, vector<string>> &adj, unordered_map<string, ll> &memo) {
    if (cur == end) return 1;
    if (memo.contains(cur)) return memo[cur];

    ll ret = 0;
    for (string &nxt: adj[cur]) {
        ret += solve(nxt, end, adj, memo);
    }

    return memo[cur] = ret;
}

ll numWays(string start, string end, unordered_map<string, vector<string>> &adj) {
    unordered_map<string, ll> memo;
    return solve(start, end, adj, memo);
}

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

    ll total = numWays("svr", "fft", adj) * numWays("fft", "dac", adj) * numWays("dac", "out", adj)
             + numWays("svr", "dac", adj) * numWays("dac", "fft", adj) * numWays("fft", "out", adj);

    cout << total << endl;
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
