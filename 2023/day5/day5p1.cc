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
    ifstream f {"day5.in"};
    string s;

    getline(f,s);
    vector<string> initial = split(s);
    vector<long> seeds;
    for (int i = 1; i < initial.size(); i++) {
        seeds.push_back(stol(initial[i]));
    }
    vector<long> newSeeds;
    getline(f,s); getline(f,s);

    while (getline(f,s)) {
        if (s == "") {
            for (long num: seeds) {
                newSeeds.push_back(num);
            }
            seeds = newSeeds;
            newSeeds.clear();
            getline(f,s); getline(f,s);
        } else {
            vector<string> vec = split(s);
            vector<long> temp;
            long dest = stol(vec[0]), source = stol(vec[1]), range = stol(vec[2]);
            for (int i = 0; i < seeds.size(); i++) {
                if (seeds[i] >= source && seeds[i] < source + range) {
                    newSeeds.push_back(dest + seeds[i] - source);
                } else {
                    temp.push_back(seeds[i]);
                }
            }
            seeds = temp;
        }
    }

    sort(newSeeds.begin(), newSeeds.end());
    cout << newSeeds[0] << endl;
    
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
