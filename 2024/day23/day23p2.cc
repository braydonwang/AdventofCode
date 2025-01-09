#include <bits/stdc++.h>

using ll = long long;

const vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};

int uid(string s) {
    return (s[0] - 'a') * 26 + (s[1] - 'a');
}

string nameFromId(int id) {
    char b = (char)(id % 26 + 'a');
    char a = (char)((id - (id % 26)) / 26 + 'a');
    string ret = "";
    ret.push_back(a); ret.push_back(b);
    return ret;
}

void search(int node, vector<int> vec, set<vector<int>> &sets, vector<vector<bool>> &adj) {
    sort(vec.begin(), vec.end());
    if (sets.contains(vec)) return;

    sets.insert(vec);
    for (int i = 0; i < 26 * 26; i++) {
        if (adj[node][i]) {
            bool contains = true;
            for (int req: vec) {
                if (!adj[i][req]) {
                    contains = false;
                    break;
                }
            }
            if (contains) {
                vector<int> newvec = vec;
                newvec.push_back(i);
                search(i, newvec, sets, adj);
            }
        }
    }
}

int main() {
    ifstream f {"day23.in"};
    string s;
    vector<vector<bool>> adj(26 * 26, vector<bool>(26 * 26));

    while (getline(f, s)) {
        int idx = s.find('-');
        string a = s.substr(0, idx), b = s.substr(idx+1);
        int ua = uid(a), ub = uid(b);
        adj[ua][ub] = true; adj[ub][ua] = true;
    }

    set<vector<int>> sets;
    for (int i = 0; i < 26 * 26; i++) {
        search(i, {i}, sets, adj);
    }

    int ans = 0;
    string str = "";

    for (vector<int> vec: sets) {
        if (vec.size() > ans) {
            string tmp = "";
            for (int node: vec) {
                string name = nameFromId(node);
                if (!tmp.empty()) tmp.push_back(',');
                tmp += name;
            }
            str = tmp;
            ans = vec.size();
        }
    }

    cout << str << endl;
}
