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
vector<int> splitInt(string s, char ch);

ll find(string str, vector<int> conds, int ind, int bind, int len, vector<vector<vector<ll>>> &dp) {
    if (ind == str.length()) {
        if (bind == conds.size() && len == 0) {
            return 1;
        } else if (bind == conds.size() - 1 && len == conds[bind]) {
            return 1;
        } else {
            return 0;
        }
    }
    if (dp[ind][bind][len] != -1) return dp[ind][bind][len];

    ll ans = 0;
    if (str[ind] == '?' || str[ind] == '.') {
        if (len == 0) {
            ans +=  find(str,conds,ind+1,bind,0,dp);
        } else if (len > 0 && bind < conds.size() && len == conds[bind]) {
            ans += find(str,conds,ind+1,bind+1,0,dp);
        }
    }

    if (str[ind] == '?' || str[ind] == '#') {
        ans += find(str,conds,ind+1,bind,len+1,dp);
    }
    return dp[ind][bind][len] = ans;
}

int main() {
    ifstream f {"day12.in"};
    string s;
    ll ans = 0;

    while (getline(f,s)) {
        vector<string> vec = split(s);
        string str = vec[0];
        vector<int> conds = splitInt(vec[1],',');
        string newStr = str;
        vector<int> newConds = conds;

        for (int i = 0; i < 4; i++) {
            newStr += '?' + str;
            for (int num: conds) {
                newConds.push_back(num);
            }
        }

        int n = newStr.length(), m = newConds.size();
        vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(m + 1, vector<ll>(n, -1)));
        ans += find(newStr, newConds, 0, 0, 0, dp);
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

vector<int> splitInt(string s, char ch) {
    stringstream ss(s);
    vector<int> vec;

    for (int i; ss >> i;) {
        vec.push_back(i);
        if (ss.peek() == ch) {
            ss.ignore();
        }
    }
    return vec;
}
