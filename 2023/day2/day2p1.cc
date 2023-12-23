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

bool check(unordered_map<string, int> freq) {
    for (auto x: freq) {
        string col = x.first;
        if (col == "red" && x.second > 12) {
            return false;
        } else if (col == "green" && x.second > 13) {
            return false;
        } else if (col == "blue" && x.second > 14) {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream f {"day2.in"};
    string s;
    int sum = 0;

    while (getline(f,s)) {
        vector<string> vec = split(s);
        int id = stoi(vec[1]);
        unordered_map<string,int> freq;
        bool valid = true;

        int ind = 2;
        while (ind < vec.size()) {
            int num = stoi(vec[ind]);
            string color = ind == vec.size() - 2 ? vec[ind+1] : vec[ind+1].substr(0,vec[ind+1].size() - 1);
            freq[color] += num;

            if (ind == vec.size() - 2 || vec[ind+1][vec[ind+1].size()-1] == ';') {
                valid &= check(freq);
                freq.clear();
                if (!valid) {
                    break;
                }
            }

            ind += 2;
        }

        if (valid) {
            sum += id;
        }
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
