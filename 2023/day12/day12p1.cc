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

int ans = 0;

bool check(string str, vector<int> conds) {
    int len = 0;
    vector<int> cur;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '.') {
            if (len > 0) {
                cur.push_back(len);
            }
            len = 0;
        } else {
            len++;
        }
    }
    if (len > 0) cur.push_back(len);
    return cur == conds;
}

void recurse(string str, int ind, vector<int> conds) {
    if (ind == str.length()) {
        if (check(str,conds)) ans++;
        return;
    }

    if (str[ind] != '?') {
        recurse(str,ind+1,conds);
    } else {
        str[ind] = '.';
        recurse(str,ind+1,conds);
        str[ind] = '#';
        recurse(str,ind+1,conds);
    }
}

int main() {
    ifstream f {"day12.in"};
    string s;

    while (getline(f,s)) {
        vector<string> vec = split(s);
        string str = vec[0];
        vector<int> conds = splitInt(vec[1],',');
        
        recurse(str, 0, conds);
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
