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

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

int isNum(int &i, string &s) {
    string num = "";
    int ind = i;
    while (ind < s.length()) {
        if (!isDigit(s[ind])) break;
        num += s[ind];
        if (num.length() > 3) return -1;
        ind++;
    }
    if (num.empty()) return -1;
    i = ind;
    return stoi(num);
}

int valid(int i, ll &sum, string &s) {
    if (i+4 >= s.length() || s.substr(i,4) != "mul(") {
        return -1;
    }

    i += 4;
    int a = isNum(i, s);
    if (a == -1) return -1;

    if (i >= s.length() || s[i] != ',') {
        return -1;
    }

    i++;
    int b = isNum(i, s);
    if (b == -1) return -1;

    if (i >= s.length() || s[i] != ')') {
        return -1;
    }

    sum += (ll)a * b;
    return i;
}

int main() {
    ifstream f {"day3.in"};
    string s;
    ll sum = 0;

    while (getline(f,s)) {
        int ind = 0;
        while (ind < s.length()) {
            int good = valid(ind, sum, s);
            if (good != -1) {
                ind = good;
            } else {
                ind++;
            }
        }
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
