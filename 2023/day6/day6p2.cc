#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <unordered_map>
#include <regex>
#include <string>

using namespace std;
#define ll long long

vector<string> split(string s);

ll calc(ll hold, ll time) {
    return (time - hold) * hold;
}

int main() {
    ifstream f {"day6.in"};
    string s;
    ll prod = 1;

    getline(f,s);
    vector<string> vec = split(s);
    vector<ll> time;
    string str = "";
    for (int i = 1; i < vec.size(); i++) {
        str += vec[i];
    }
    time.push_back(stol(str));

    getline(f,s);
    vec = split(s);
    vector<ll> dist;
    str = "";
    for (int i = 1; i < vec.size(); i++) {
        str += vec[i];
    }
    dist.push_back(stol(str));

    for (int i = 0; i < time.size(); i++) {
        ll lo = 0, hi = time[i];
        ll l = 0, r = 0;
        while (lo <= hi) {
            ll mid = (lo + hi) / 2;
            ll travel = calc(mid, time[i]);
            if (travel > dist[i]) {
                l = mid;
                hi = mid - 1;
            } else {
                if (calc(mid + 1, time[i]) >= travel) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
        }

        lo = 0; hi = time[i];
        while (lo <= hi) {
            ll mid = (lo + hi) / 2;
            ll travel = calc(mid, time[i]);
            if (travel > dist[i]) {
                r = mid;
                lo = mid + 1;
            } else {
                if (calc(mid + 1, time[i]) >= travel) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
        }
        prod *= (r - l + 1);
    }
    
    cout << prod << endl;

    return 0;
}

vector<string> split(string s) {
    stringstream ss(s);
    string str;
    vector<string> vec;

    while (ss >> str) {
        vec.push_back(str);
    }
    return vec;
}
