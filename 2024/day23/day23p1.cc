#include <bits/stdc++.h>

using ll = long long;

const vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};

int uid(string s) {
    return (s[0] - 'a') * 26 + (s[1] - 'a');
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

    set<vector<int>> seen;
    for (int i = uid("ta"); i <= uid("tz"); i++) {
        vector<int> vec;
        for (int j = 0; j < 26 * 26; j++) {
            if (adj[i][j]) {
                vec.push_back(j);
            }
        }
        for (int j = 0; j < vec.size(); j++) {
            for (int k = j+1; k < vec.size(); k++) {
                if (adj[vec[j]][vec[k]]) {
                    vector<int> add = {i, vec[j], vec[k]};
                    sort(add.begin(), add.end());
                    seen.insert(add);
                }
            }
        }
    }

    cout << seen.size() << endl;
}
