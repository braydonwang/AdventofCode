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
vector<string> split(string s);

int main() {
    ifstream f {"day1.in"};
    string s;
    ll ans = 0, sum = 0;

    getline(f, s);
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            sum++;
        } else {
            sum--;
            if (sum < 0) {
                ans = i+1;
                break;
            }
        }
    }
    
    cout << ans << endl;
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
