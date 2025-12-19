#include <bits/stdc++.h>
using ll = long long;

vector<string> split(string s, char delim = ' ');

int main() {
    ifstream f {"day5.in"};
    string s;
    vector<pair<ll,ll>> ranges;

    while (getline(f, s)) {
        if (s.empty()) break;
        vector<string> v = split(s, '-');
        ranges.push_back({stoll(v[0]), stoll(v[1])});
    }

    vector<pair<ll,ll>> merged;
    sort(ranges.begin(), ranges.end());

    ll l = ranges[0].first, r = ranges[0].second;
    for (int i = 1; i < ranges.size(); i++) {
        if (ranges[i].first <= r) {
            r = max(r, ranges[i].second);
        } else {
            merged.push_back({l, r});
            l = ranges[i].first;
            r = ranges[i].second;
        }
    }
    merged.push_back({l, r});

    int ans = 0;
    while (getline(f, s)) {
        if (s.empty()) break;
        ll num = stoll(s);
        auto it = upper_bound(merged.begin(), merged.end(), make_pair(num, LLONG_MAX));
        if (it != merged.begin()) {
            --it;
            if (it->first <= num && it->second >= num) ans++;
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
