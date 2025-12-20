#include <bits/stdc++.h>
using ll = long long;

vector<string> split(string s, char delim = ' ');

ll sqr(ll x) {
    return x * x;
}

ll findDis(int x1, int y1, int z1, int x2, int y2, int z2) {
    return sqr(x1 - x2) + sqr(y1 - y2) + sqr(z1 - z2);
}

int find(int i, vector<int> &parent) {
    if (parent[i] != i) {
        return parent[i] = find(parent[i], parent);
    }
    return i;
}

void merge(int x, int y, vector<int> &parent, vector<int> &rank) {
    int xroot = find(x, parent), yroot = find(y, parent);
    if (xroot == yroot) return;

    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else if (rank[yroot] < rank[xroot]) {
        parent[yroot] = xroot;
    } else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

int main() {
    ifstream f {"day8.in"};
    string s;
    vector<vector<int>> coords;

    while (getline(f, s)) {
        if (s.empty()) break;
        vector<string> v = split(s, ',');
        coords.push_back({stoi(v[0]), stoi(v[1]), stoi(v[2])});
    }

    int sz = coords.size();
    vector<vector<ll>> dis;

    for (int i = 0; i < sz; i++) {
        for (int j = i+1; j < sz; j++) {
            ll d = findDis(coords[i][0], coords[i][1], coords[i][2], coords[j][0], coords[j][1], coords[j][2]);
            dis.push_back({d, i, j});
        }
    }

    sort(dis.begin(), dis.end());
    vector<int> parent(sz), rank(sz);
    for (int i = 0; i < sz; i++) parent[i] = i;

    int connects = 0, i = 0;
    for (; i < dis.size() && connects < sz-1; i++) {
        vector<ll> cur = dis[i];
        if (find((int)cur[1], parent) != find((int)cur[2], parent)) {
            merge((int)cur[1], (int)cur[2], parent, rank);
            connects++;
        }
    }
    i--;

    int ind1 = (int)dis[i][1], ind2 = (int)dis[i][2];
    ll ans = (ll)coords[ind1][0] * coords[ind2][0];

    cout << ans << endl;
}

vector<string> split(string s, char delim) {
    vector<string> vec;
    string acc = "";

    for (char ch: s) {
        if (ch == delim) {
            vec.push_back(acc);
            acc = "";
        } else {
            acc += ch;
        }
    }

    if (!acc.empty()) vec.push_back(acc);
    return vec;
}
