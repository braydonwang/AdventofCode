#include <bits/stdc++.h>

using ll = long long;

const map<vector<int>, char> dir = {{{0,1},'>'},{{0,-1},'<'},{{1,0},'v'},{{-1,0},'^'}};

const vector<vector<char>> numpad = {
    {'7', '8', '9'},
    {'4', '5', '6'},
    {'1', '2', '3'},
    {'*', '0', 'A'},
};

const vector<vector<char>> dirpad = {
    {'*', '^', 'A'},
    {'<', 'v', '>'},
};

struct Node {
    pair<int,int> pos;
    string seq;
    Node(pair<int,int> pos, string seq) : pos{pos}, seq{seq} {}
};

map<pair<char,char>, vector<string>> numpaths;
map<pair<char,char>, vector<string>> dirpaths;
map<pair<char, char>, int> dirlens;
map<pair<string, int>, ll> memo;

map<pair<char,char>, vector<string>> precompute(const vector<vector<char>> &pad) {
    map<char, pair<int,int>> pos;
    map<pair<char,char>, vector<string>> paths;

     for (int i = 0; i < pad.size(); i++) {
        for (int j = 0; j < pad[i].size(); j++) {
            if (pad[i][j] != '*') {
                pos[pad[i][j]] = {i, j};
            }
        }
    }

    for (auto &[a, _]: pos) {
        for (auto &[b, _]: pos) {
            if (a == b) {
                paths[{a, b}] = {"A"};
                continue;
            }

            queue<Node> q;
            vector<string> options;
            q.push(Node(pos[a], ""));
            int best = INT_MAX;

            while (!q.empty()) {
                Node n = q.front(); q.pop();
                for (auto &[d, ch]: dir) {
                    int nr = n.pos.first + d[0], nc = n.pos.second + d[1];
                    if (nr < 0 || nr >= pad.size() || nc < 0 || nc >= pad[0].size()) continue;
                    if (pad[nr][nc] == '*') continue;

                    if (pad[nr][nc] == b) {
                        if (best < n.seq.length() + 1) {
                            goto end;
                        }
                        best = n.seq.length() + 1;
                        options.push_back(n.seq + ch + 'A');
                    } else {
                        q.push(Node({nr, nc}, n.seq + ch));
                    }
                }
            } end:

            paths[{a, b}] = options;
        }
    }

    return paths;
}

void solve(string &s, map<pair<char,char>, vector<string>> &paths, vector<string> &poss) {
    vector<string> ret = {""};
    for (int i = 0; i < s.length(); i++) {
        char a;
        if (i == 0) a = 'A';
        else a = s[i-1];
        char b = s[i];
        vector<string> all = paths[{a, b}];

        vector<string> nret;
        for (string p: all) {
            for (string og: ret) {
                nret.push_back(og + p);
            }
        }

        ret = nret;
    }

    if (!poss.empty() && poss.front().length() < ret.front().length()) return;
    if (poss.empty() || poss.front().length() > ret.front().length()) {
        poss = ret;
        return;
    }

    for (string &p: ret) {
        poss.push_back(p);
    }
}

ll compute(string seq, int depth) {
    if (memo.contains({seq, depth})) {
        return memo[{seq, depth}];
    }

    ll total = 0;
    string oseq = seq;
    seq = 'A' + seq;
    if (depth == 0) {
        for (int i = 0; i < seq.length() - 1; i++) {
            char a = seq[i], b = seq[i+1];
            total += dirlens[{a, b}];
        }
    } else {
        for (int i = 0; i < seq.length() - 1; i++) {
            char a = seq[i], b = seq[i+1];
            ll best = LLONG_MAX;
            for (string &np: dirpaths[{a, b}]) {
                best = min(best, compute(np, depth - 1));
            }
            total += best;
        }
    }

    memo[{oseq, depth}] = total;
    return total;
}

int main() {
    ifstream f {"day21.in"};
    string s;
    ll ans = 0;

    numpaths = precompute(numpad);
    dirpaths = precompute(dirpad);

    for (auto &[p, vec]: dirpaths) {
        dirlens[p] = vec[0].length();
    }

    while (getline(f, s)) {
        vector<string> poss;
        solve(s, numpaths, poss);

        ll len = LLONG_MAX;
        for (string &p: poss) {
            len = min(len, compute(p, 24));
        }

        ans += stoll(s.substr(0, s.length() - 1)) * len;
    }

    cout << ans << endl;
}
