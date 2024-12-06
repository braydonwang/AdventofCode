#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <regex>

using ll = long long;

using namespace std;
vector<int> split(string s, char delim);

bool valid(vector<int> &vec, unordered_map<int, unordered_set<int>> &adj) {
    for (int i = 0; i < vec.size() - 1; i++) {
        if (!adj[vec[i]].contains(vec[i+1])) return false;
    }
    return true;
}

int main() {
    ifstream f {"day5.in"};
    string s;
    ll sum = 0;
    unordered_map<int, unordered_set<int>> adj;
    unordered_map<int, int> in;

    while (getline(f,s)) {
        if (s.empty()) break;
        vector<int> vec = split(s, '|');
        adj[vec[0]].insert(vec[1]);
        in[vec[1]]++;
        if (!in.contains(vec[0])) in[vec[0]] = 0;
    }

    while (getline(f,s)) {
        vector<int> vec = split(s, ',');
        if (!valid(vec, adj)) {
            unordered_map<int, int> indegree;
            queue<int> q;
            for (int num: vec) {
                if (!indegree.contains(num)) indegree[num] = 0;
                for (int nxt: adj[num]) {
                    if (find(vec.begin(), vec.end(), nxt) != vec.end()) {
                        indegree[nxt]++;
                    }
                }
            }
            for (int num: vec) {
                if (indegree[num] == 0) q.push(num);
            }
            vector<int> newvec;
            while (!q.empty()) {
                int cur = q.front(); q.pop();
                newvec.push_back(cur);
                for (int nxt: adj[cur]) {
                    if (find(vec.begin(), vec.end(), nxt) == vec.end()) continue;
                    indegree[nxt]--;
                    if (indegree[nxt] == 0) q.push(nxt);
                }
            }
            sum += newvec[newvec.size()/2];
        }
    }

    cout << sum << endl;
}

vector<int> split(string s, char delim) {
    int ind = 0, acc = 0;
    vector<int> vec;

    while (ind < s.length()) {
        if (s[ind] == delim) {
            vec.push_back(acc);
            acc = 0;
        } else {
            acc = acc * 10 + s[ind] - '0';
        }
        ind++;
    }
    vec.push_back(acc);

    return vec;
}
