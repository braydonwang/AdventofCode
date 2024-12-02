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

int main() {
    ifstream f {"day2.in"};
    string s;
    ll sum = 0;

    while (getline(f,s)) {
        vector<int> vec = split(s);
        bool inc = false, dec = false, safe = true;

        for (int i = 1; i < vec.size(); i++) {
            int diff = vec[i] - vec[i-1];
            if ((diff > 0 && dec) || (diff < 0 && inc) || abs(diff) < 1 || abs(diff) > 3) {
                safe = false;
                break;
            }
            if (diff > 0) inc = true;
            else dec = true;
        }

        if (safe) sum++;
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
