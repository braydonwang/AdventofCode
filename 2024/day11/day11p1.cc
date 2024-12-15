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
    int times = 25;

    while (times--) {
        vector<ll> newstones;
        for (int i = 0; i < stones.size(); i++) {
            if (stones[i] == 0) {
                newstones.push_back(1);
            } else {
                string str = to_string(stones[i]);
                if (str.length() % 2 == 0) {
                    string l = str.substr(0, str.length() / 2), r = str.substr(str.length() / 2);
                    newstones.push_back(stoi(l));
                    newstones.push_back(stoi(r));
                } else {
                    newstones.push_back(stones[i] * 2024);
                }
            }
        }
        stones = newstones;
    }

    cout << stones.size() << endl;
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
