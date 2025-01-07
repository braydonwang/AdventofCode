#include <bits/stdc++.h>

using ll = long long;

const vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};

struct Trie {
    unordered_map<char, Trie*> children;
    bool valid;

    Trie() : valid(false) {}
};

vector<string> split(string &s) {
    vector<string> vec;
    int ind = 0;
    string acc = "";

    while (ind < s.length()) {
        if (s[ind] == ',') {
            vec.push_back(acc);
            acc = "";
            ind++;
        } else {
            acc += s[ind];
        }
        ind++;
    }

    vec.push_back(acc);
    return vec;
}

Trie *makeTrie(vector<string> &towels) {
    Trie *root = new Trie();
    for (string &s: towels) {
        Trie *cur = root;
        for (char ch: s) {
            if (!cur->children.contains(ch)) {
                cur->children[ch] = new Trie();
            }
            cur = cur->children[ch];
        }
        cur->valid = true;
    }
    return root;
}

bool rec(int ind, string &s, Trie *root, vector<int> &dp) {
    if (ind >= s.length()) return true;
    if (dp[ind] != -1) return dp[ind];

    dp[ind] = 0;
    Trie *cur = root;
    for (int i = ind; i < s.length(); i++) {
        if (!cur->children.contains(s[i])) break;
        cur = cur->children[s[i]];

        if (cur->valid && rec(i+1, s, root, dp)) {
            dp[ind] = 1;
            break;
        }
    }

    return dp[ind];
}

bool good(string &s, Trie *root) {
    vector<int> dp(s.length(), -1);

    return rec(0, s, root, dp);
}

int main() {
    ifstream f {"day19.in"};
    string s;

    getline(f, s);
    vector<string> towels = split(s);

    Trie *root = makeTrie(towels);
    int ans = 0;

    getline(f, s);
    while (getline(f, s)) {
        if (good(s, root)) {
            ans++;
        }
    }

    cout << ans << endl;
}
