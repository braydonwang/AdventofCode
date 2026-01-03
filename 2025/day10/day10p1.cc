#include <bits/stdc++.h>
using ll = long long;

vector<string> split(string s, char delim = ' ');

char toggle(char ch) {
    return ch == '.' ? '#' : '.';
}

int solve(string &target, vector<vector<int>> &actions) {
    queue<string> q;
    unordered_map<string, int> dis;
    string init = string(target.length(), '.');
    q.push(init);
    dis[init] = 0;

    while (!q.empty()) {
        string cur = q.front(); q.pop();
        for (vector<int> &a: actions) {
            string nxt = cur;
            for (int ind: a) {
                nxt[ind] = toggle(nxt[ind]);
            }
            if (!dis.contains(nxt)) {
                dis[nxt] = dis[cur] + 1;
                if (nxt == target) break;
                q.push(nxt);
            }
        }
    }

    return dis[target];
}

int main() {
    ifstream f {"day10.in"};
    string s;
    ll ans = 0;

    while (getline(f, s)) {
        if (s.empty()) break;
        vector<string> v = split(s);
        v.pop_back();

        string target = v[0].substr(1, v[0].length()-2);
        vector<vector<int>> actions;
        for (int i = 1; i < v.size(); i++) {
            vector<string> tmp = split(v[i].substr(1, v[i].length()-2),',');
            vector<int> a(tmp.size());
            for (int j = 0; j < tmp.size(); j++) {
                a[j] = stoi(tmp[j]);
            }
            actions.push_back(a);
        }

        ans += solve(target, actions);
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
