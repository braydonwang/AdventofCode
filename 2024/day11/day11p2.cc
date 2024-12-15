#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <regex>

using ll = long long;
using namespace std;

vector<ll> split(string s);

int main() {
    ifstream f {"day11.in"};
    string s;
    getline(f, s);

    vector<ll> stones = split(s);
    unordered_map<string, ll> cnt;

    for (ll st: stones) cnt[to_string(st)]++;

    int times = 75;
    while (times--) {
        unordered_map<string, ll> newcnt;

        for (auto &[st, freq]: cnt) {
            if (st == "0") {
                newcnt["1"] += freq;
            } else if (st.length() % 2 == 0) {
                string l = to_string(stoll(st.substr(0, st.length()/2)));
                string r = to_string(stoll(st.substr(st.length()/2)));
                newcnt[l] += freq;
                newcnt[r] += freq;
            } else {
                string newst = to_string(stoll(st) * (ll)2024);
                newcnt[newst] += freq;
            }
        }

        cnt = newcnt;
    }

    ll ans = 0;
    for (auto &[st, freq]: cnt) {
        ans += freq;
    }

    cout << ans << endl;
}

vector<ll> split(string s) {
    stringstream ss(s);
    vector<ll> vec;
    ll num;
    while (ss >> num) {
        vec.push_back(num);
    }
    return vec;
}
