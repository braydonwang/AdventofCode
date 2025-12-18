#include <bits/stdc++.h>
using ll = long long;

vector<string> split(string s, char delim = ' ');

bool invalid(ll num) {
    string s = to_string(num);
    if (s.length() % 2 != 0) return false;
    string a = s.substr(0, s.length()/2), b = s.substr(s.length()/2);
    return a == b;
}

int main() {
    ifstream f {"day2.in"};
    string s;
    ll sum = 0;

    while (getline(f, s)) {
        if (s.empty()) break;
        vector<string> vec = split(s, ',');

        for (string v: vec) {
            vector<string> input = split(v, '-');
            ll l = stoll(input[0]), r = stoll(input[1]);
            while (l <= r) {
                if (invalid(l)) {
                    sum += l;
                }
                l++;
            }
        }
    }

    cout << sum << endl;
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
