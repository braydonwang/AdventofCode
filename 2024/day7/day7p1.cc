#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <regex>

using ll = long long;
using namespace std;

vector<string> split(string s, char delim);
vector<ll> split(string s);

bool valid(ll acc, int ind, ll target, vector<ll> &nums) {
    if (acc > target) return false;
    if (ind == nums.size()) return acc == target;

    return valid(acc + nums[ind], ind+1, target, nums)
        || valid(acc * nums[ind], ind+1, target, nums);
}

int main() {
    ifstream f {"day7.in"};
    string s;
    ll sum = 0;

    while (getline(f,s)) {
        vector<string> vec = split(s, ':');
        ll target = stoll(vec[0]);
        vector<ll> nums = split(vec[1].substr(1));

        if (valid(0, 0, target, nums)) sum += target;
    }

    cout << sum << endl;
}

vector<string> split(string s, char delim) {
    int ind = 0;
    string acc = "";
    vector<string> vec;

    while (ind < s.length()) {
        if (s[ind] == delim) {
            vec.push_back(acc);
            acc = "";
        } else {
            acc += s[ind];
        }
        ind++;
    }
    vec.push_back(acc);
    return vec;
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
