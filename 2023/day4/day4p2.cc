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
vector<string> split(string s);

int main() {
    ifstream f {"day4.in"};
    string s;
    long sum = 0;
    int numCards = 0;
    vector<string> input;

    while (getline(f,s)) {
        numCards++;
        input.push_back(s);
    }

    vector<int> freq(numCards, 1);

    for (int i = 0; i < input.size(); i++) {
        vector<string> vec = split(input[i]);
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
                        points++;
                    }
                }
            }
            ind++;
        }

        for (int j = 1; j <= points; j++) {
            freq[i+j] += freq[i];
        }
    }

    for (int num: freq) {
        sum += num;
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
