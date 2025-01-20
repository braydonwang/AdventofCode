#include <bits/stdc++.h>

using ll = long long;

vector<string> split(string &s);

int ans = 0;

void floydWarshall(vector<vector<int>> &dis, int sz) {
    for (int k = 0; k < sz; k++) {
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                if (dis[i][k] != INT_MAX && dis[k][j] != INT_MAX && dis[i][j] > dis[i][k] + dis[k][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
}

void solve(int cur, int time, int total, vector<bool> &vis, vector<int> &rate, vector<vector<int>> &dis) {
    total += rate[cur] * time;
    ans = max(ans, total);

    for (int nxt = 0; nxt < vis.size(); nxt++) {
        if (nxt == cur || vis[nxt] || rate[nxt] == 0) continue;
        if (dis[cur][nxt] + 1 >= time) continue;
        
        vis[nxt] = true;
        solve(nxt, time - dis[cur][nxt] - 1, total, vis, rate, dis);
        vis[nxt] = false;
    }
}

int main() {
    ifstream f {"day16.in"};
    string s;

    unordered_map<string,vector<string>> adj;
    unordered_map<string,int> inds;
    vector<int> rate;

    while (getline(f,s)) {
        vector<string> vec = split(s);
        string name = vec[1];
        inds[name] = inds.size();

        int amt = stoi(vec[4].substr(5, vec[4].length() - 6));
        rate.push_back(amt);

        for (int i = 9; i < vec.size(); i++) {
            if (i == vec.size() - 1) {
                adj[name].push_back(vec[i]);
            } else {
                adj[name].push_back(vec[i].substr(0,vec[i].length()-1));
            }
        }
    }

    int sz = inds.size();
    vector<bool> vis(sz);
    vector<vector<int>> dis(sz, vector<int>(sz, INT_MAX));

    for (auto &[name, vec]: adj) {
        int a = inds[name];
        dis[a][a] = 0;
        for (string &nxt: vec) {
            int b = inds[nxt];
            dis[a][b] = 1;
        }
    }

    floydWarshall(dis, sz);

    solve(inds["AA"], 30, 0, vis, rate, dis);

    cout << ans << endl; 
}

vector<string> split(string &s) {
    vector<string> vec;
    string acc = "";
    int ind = 0;
    while (ind < s.length()) {
        if (s[ind] == ' ') {
            vec.push_back(acc);
            acc = "";
        } else {
            acc += s[ind];
        }
        ind++;
    }
    vec.push_back(acc);
    return vec;
}
