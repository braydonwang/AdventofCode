#include <bits/stdc++.h>
using ll = long long;

vector<string> split(string s, char delim = ' ');

int main() {
    ifstream f {"day12.in"};
    string s;
    int cnt = 0;

    while (getline(f, s)) {
        if (s.empty()) {
            cnt++;
            if (cnt == 6) break;
        }
    }

    ll ans = 0;
    while (getline(f, s)) {
        if (s.empty()) break;
        vector<string> v = split(s);
        vector<string> dim = split(v[0].substr(0, v[0].length()-1), 'x');
        ll w = stoll(dim[0]), l = stoll(dim[1]);
        ll num = 0;
        for (int i = 1; i < v.size(); i++) {
            num += stoll(v[i]);
        }

        if (num <= w * l / 9) ans++;
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
