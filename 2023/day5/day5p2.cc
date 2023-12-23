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

bool compare(pair<long,long> p1, pair<long,long> p2) {
    if (p1.first == p2.first) {
        return p1.second < p2.second;
    }
    return p1.first < p2.first;
}

int main() {
    ifstream f {"day5.in"};
    string s;

    getline(f,s);
    vector<string> initial = split(s);
    vector<pair<long,long>> seeds;
    for (int i = 1; i < initial.size(); i+=2) {
        seeds.push_back({stol(initial[i]), stol(initial[i]) + stol(initial[i+1]) - 1});
    }
    vector<pair<long,long>> newSeeds;
    getline(f,s); getline(f,s);

    while (getline(f,s)) {
        if (s == "") {
            for (pair<long,long> p: seeds) {
                newSeeds.push_back(p);
            }

            seeds = newSeeds;
            newSeeds.clear();
            getline(f,s);
        } else {
            vector<string> vec = split(s);
            vector<pair<long,long>> temp;
            long dest = stol(vec[0]), source = stol(vec[1]), range = stol(vec[2]);
            long end = source + range - 1;
            for (int i = 0; i < seeds.size(); i++) {
                long l = seeds[i].first, r = seeds[i].second;
                if (end < l || source > r) {
                    temp.push_back(seeds[i]);
                } else if (source <= l && end >= r) {
                    newSeeds.push_back({dest + l - source, dest + r - source});
                } else if (l < source && r <= end) {
                    newSeeds.push_back({dest, dest + r - source});
                    temp.push_back({l, source - 1});
                } else if (r > end && l >= source) {
                    newSeeds.push_back({dest + l - source, dest + range});
                    temp.push_back({end + 1, r});
                } else if (l < source && r > end) {
                    newSeeds.push_back({dest, dest + range});
                    temp.push_back({l, source - 1});
                    temp.push_back({end + 1, r});
                }
            }
            seeds = temp;
        }
    }

    for (pair<long,long> p: seeds) {
        newSeeds.push_back(p);
    }

    sort(newSeeds.begin(), newSeeds.end(), compare);
    
    cout << newSeeds[0].first << endl;
    
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
