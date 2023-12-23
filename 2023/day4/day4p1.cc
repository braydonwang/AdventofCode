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

using namespace std;
vector<string> split(string s);

int main() {
    ifstream f {"day4.in"};
    string s;
    int sum = 0;

    while (getline(f,s)) {
        vector<string> vec = split(s);
        int ind = 2;
        bool winning = true;
        set<string> win;
        int points = 0;

        while (ind < vec.size()) {
            if (vec[ind] == "|") {
                winning = false;
            } else {
                if (winning) {
                    win.insert(vec[ind]);
                } else {
                    if (win.count(vec[ind]) != 0) {
                        points = points == 0 ? 1 : points * 2;
                    }
                }
            }
            ind++;
        }

        sum += points;
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
