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
vector<string> splitStr(string s, char ch);

int hsh(string str) {
    int cur = 0;
    for (char ch: str) {
        cur = (cur + ch) * 17 % 256;
    }
    return cur;
}

int main() {
    ifstream f {"day15.in"};
    string s;
    ll ans = 0;

    getline(f,s);
    vector<string> steps = splitStr(s, ',');
    vector<vector<pair<string,int>>> boxes(256,vector<pair<string,int>>());

    for (string str: steps) {
        int len = str.length();
        if (str[len-1] == '-') {
            string label = str.substr(0,len-1);
            int num = hsh(label);
            vector<pair<string,int>> &box = boxes[num];
            for (int i = 0; i < box.size(); i++) {
                if (box[i].first == label) {
                    box.erase(box.begin() + i);
                    break;
                }
            }
        } else {
            string label = str.substr(0,len-2);
            int num = hsh(label);
            int focus = stoi(str.substr(len-1,1));
            bool found = false;
            vector<pair<string,int>> &box = boxes[num];
            
            for (int i = 0; i < box.size(); i++) {
                if (box[i].first == label) {
                    box[i].second = focus;
                    found = true;
                    break;
                }
            }
            if (!found) box.push_back({label,focus});
        }
    }

    for (int i = 0; i < 256; i++) {
        int ind = 1;
        for (pair<string,int> p: boxes[i]) {
            ans += (i + 1) * ind * p.second;
            ind++;
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

vector<string> splitStr(string s, char ch) {
    stringstream ss(s);
    vector<string> vec;
    while (ss.good()) {
        string str;
        getline(ss,str,',');
        vec.push_back(str);
    }
    return vec;
}
