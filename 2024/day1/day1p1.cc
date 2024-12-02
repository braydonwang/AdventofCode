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
    ll sum = 0;

    vector<int> a, b;

    while (getline(f,s)) {
        stringstream ss(s);
        int x, y;
        ss >> x >> y;

        a.push_back(x);
        b.push_back(y);
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    for (int i = 0; i < a.size(); i++) {
        sum += abs(a[i] - b[i]);
    }
    
    cout << sum << endl;
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
