#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <regex>

using ll = long long;

using namespace std;
vector<int> split(string s);

bool safe(int ind, vector<int> &vec) {
    int i = 1, prev = 0;
    bool inc = false, dec = false;
    if (ind == 0) {
        i = 2; prev = 1;
    }

    while (i < vec.size()) {
        if (i == ind) {
            i++; continue;
        }

        int diff = vec[i] - vec[prev];
        if ((diff > 0 && dec) || (diff < 0 && inc) || abs(diff) < 1 || abs(diff) > 3) {
            return false;
        }
        if (diff > 0) inc = true;
        else dec = true;
        prev = i;
        i++;
    }

    return true;
}

bool usedSafe(vector<int> &vec) {
    for (int i = 0; i < vec.size(); i++) {
        if (safe(i, vec)) return true;
    }
    return false;
}

int main() {
    ifstream f {"day2.in"};
    string s;
    ll sum = 0;

    while (getline(f,s)) {
        vector<int> vec = split(s);
        if (usedSafe(vec)) sum++;
    }
    
    cout << sum << endl;
}

vector<int> split(string s) {
    stringstream ss(s);
    int x;
    vector<int> vec;

    while (ss >> x) {
        vec.push_back(x);
    }
    return vec;
}
