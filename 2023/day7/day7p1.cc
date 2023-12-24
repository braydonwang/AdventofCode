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
#define ll long long

vector<string> split(string s);

vector<char> order = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};

int getType(vector<int> count) {
    if (count[0] == 5) {
        return 1;
    } else if (count[0] == 4) {
        return 2;
    } else if (count[0] == 3 && count[1] == 2) {
        return 3;
    } else if (count[0] == 3) {
        return 4;
    } else if (count[0] == 2 && count[1] == 2) {
        return 5;
    } else if (count[0] == 2) {
        return 6;
    } else {
        return 7;
    }
}

bool compare(pair<string,int> p1, pair<string,int> p2) {
    string h1 = p1.first, h2 = p2.first;
    unordered_map<char,int> freq1, freq2;
    vector<int> count1, count2;
    for (int i = 0; i < h1.length(); i++) {
        freq1[h1[i]]++; freq2[h2[i]]++;
    }

    for (auto it: freq1) {
        count1.push_back(it.second);
    }
    for (auto it: freq2) {
        count2.push_back(it.second);
    }

    sort(count1.begin(), count1.end(), greater<int>());
    sort(count2.begin(), count2.end(), greater<int>());

    int t1 = getType(count1), t2 = getType(count2);
    if (t1 == t2) {
        for (int i = 0; i < h1.length(); i++) {
            if (h1[i] == h2[i]) continue;
            int o1 = find(order.begin(), order.end(), h1[i]) - order.begin();
            int o2 = find(order.begin(), order.end(), h2[i]) - order.begin();
            return o1 > o2;
        }
        return 0;
    }

    return t1 > t2;
}

int main() {
    ifstream f {"day7.in"};
    string s;
    long sum = 0;
    vector<pair<string,int>> hands;

    while (getline(f,s)) {
        vector<string> vec = split(s);
        hands.push_back({vec[0], stoi(vec[1])});
    }

    sort(hands.begin(), hands.end(), compare);

    for (int i = 0; i < hands.size(); i++) {
        sum += (i + 1) * hands[i].second;
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
