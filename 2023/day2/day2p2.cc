#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <regex>

using namespace std;
vector<string> split(string s);

bool check(unordered_map<string, int> freq, int &r, int &b, int &g) {
    for (auto x: freq) {
        string col = x.first;
        if (col == "red") {
            r = max(r, x.second);
        } else if (col == "green") {
            g = max(g, x.second);
        } else if (col == "blue") {
            b = max(b, x.second);
        }
    }
    return true;
}

int main() {
    ifstream f {"day2.in"};
    string s;
    long sum = 0;

    while (getline(f,s)) {
        vector<string> vec = split(s);
        unordered_map<string,int> freq;
        int r = 0, b = 0, g = 0;

        int ind = 2;
        while (ind < vec.size()) {
            int num = stoi(vec[ind]);
            string color = ind == vec.size() - 2 ? vec[ind+1] : vec[ind+1].substr(0,vec[ind+1].size() - 1);
            freq[color] += num;

            if (ind == vec.size() - 2 || vec[ind+1][vec[ind+1].size()-1] == ';') {
                check(freq, r, b, g);
                freq.clear();
            }

            ind += 2;
        }

        sum += r * g * b;
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
