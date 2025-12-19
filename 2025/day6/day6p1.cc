#include <bits/stdc++.h>
using ll = long long;

vector<string> split(string s, char delim = ' ');

int main() {
    ifstream f {"day6.in"};
    string s;
    vector<vector<string>> input;

    while (getline(f, s)) {
        if (s.empty()) break;
        vector<string> v = split(s);
        input.push_back(v);
    }

    int sz = input.size();
    ll sum = 0;

    for (int i = 0; i < input[0].size(); i++) {
        ll total = stoll(input[0][i]);
        bool mult = input.back()[i] == "*";
        for (int j = 1; j < sz-1; j++) {
            if (mult) {
                total *= stoll(input[j][i]);
            } else {
                total += stoll(input[j][i]);
            }
        }
        sum += total;
    }

    cout << sum << endl;
}

vector<string> split(string s, char delim) {
    vector<string> vec;
    string acc = "";

    for (char ch: s) {
        if (ch == delim) {
            if (!acc.empty()) vec.push_back(acc);
            acc = "";
        } else {
            acc += ch;
        }
    }

    if (!acc.empty()) vec.push_back(acc);
    return vec;
}
