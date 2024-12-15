#include <bits/stdc++.h>

using ll = long long;

vector<string> split(string s, char delim);

pair<int,int> getCoords(int row, int col, int vr, int vc, int r, int c) {
    int times = 100;
    while (times--) {
        row = ((row + vr) % r + r) % r;
        col = ((col + vc) % c + c) % c;
    }
    return {row, col};
}

void updateQuads(pair<int,int> coords, ll &tl, ll &tr, ll &bl, ll &br, int r, int c) {
    int row = coords.first, col = coords.second;
    if (row < r / 2) {
        if (col < c / 2) tl++;
        else if (col > c / 2) tr++;
    } else if (row > r / 2) {
        if (col < c / 2) bl++;
        else if (col > c / 2) br++;
    }
}

int main() {
    ifstream f {"day14.in"};
    string s;
    int r = 103, c = 101;
    ll tl = 0, tr = 0, bl = 0, br = 0;
    
    while (getline(f, s)) {
        vector<string> vec = split(s, ' ');
        vector<string> coords = split(vec[0].substr(2), ',');
        vector<string> vels = split(vec[1].substr(2), ',');

        int row = stoi(coords[1]), col = stoi(coords[0]);
        int vr = stoi(vels[1]), vc = stoi(vels[0]);

        pair<int,int> newcoords = getCoords(row, col, vr, vc, r, c);
        updateQuads(newcoords, tl, tr, bl, br, r, c);
    }

    ll ans = tl * tr * bl * br;
    cout << ans << endl;
}

vector<string> split(string s, char delim) {
    int ind = 0;
    string acc = "";
    vector<string> vec;

    while (ind < s.length()) {
        if (s[ind] == delim) {
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
