#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <unordered_map>
#include <map>
#include <regex>
#include <string>

using namespace std;
#define ll long long

vector<string> split(string s);
vector<int> splitInt(string s, char ch);

bool compare(vector<int> &v1, vector<int> &v2) {
    return v1[2] < v2[2];
}

bool intersect(vector<int> a, vector<int> b) {
    return max(a[0],b[0]) <= min(a[3],b[3]) && max(a[1],b[1]) <= min(a[4],b[4]);
}

int main() {
    ifstream f {"day22.in"};
    string s;
    vector<vector<int>> bricks;

    while (getline(f,s)) {
        replace(s.begin(), s.end(), '~', ',');
        bricks.push_back(splitInt(s,','));
    }

    sort(bricks.begin(), bricks.end(), compare);
    for (int i = 0; i < bricks.size(); i++) {
        int maxZ = 1;
        vector<int> &brick = bricks[i];
        for (int j = 0; j < i; j++) {
            if (intersect(brick,bricks[j])) {
                maxZ = max(maxZ,bricks[j][5]+1);
            }
        }
        brick[5] = maxZ + brick[5] - brick[2];
        brick[2] = maxZ;
    }

    unordered_map<int,vector<int>> supp;
    unordered_map<int,vector<int>> dep;
    sort(bricks.begin(), bricks.end(), compare);

    for (int i = 0; i < bricks.size(); i++) {
        vector<int> brick = bricks[i];
        for (int j = 0; j < i; j++) {
            if (intersect(brick,bricks[j]) && bricks[j][5] + 1 == brick[2]) {
                if (supp.find(j) == supp.end()) supp[j] = {};
                if (dep.find(i) == dep.end()) dep[i] = {};
                supp[j].push_back(i);
                dep[i].push_back(j);
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i < bricks.size(); i++) {
        bool valid = true;
        for (int num: supp[i]) {
            if (dep[num].size() == 1) {
                valid = false;
                break;
            }
        }
        if (valid) ans++;
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
