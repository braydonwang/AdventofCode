#include <bits/stdc++.h>

using ll = long long;

vector<string> split(string s);

int findMin(int x1, int y1, int x2, int y2, int tx, int ty) {
    int ans = INT_MAX;

    for (int b = 0; b < 100; b++) {
        int dx = tx - x2 * b, dy = ty - y2 * b;
        if (dx < 0 || dy < 0) break;

        if (dx % x1 != 0 || dy % y1 != 0 || dx / x1 != dy / y1) continue;
        ans = min(ans, dx / x1 * 3 + b);
    }

    return ans == INT_MAX ? -1 : ans;
}

int main() {
    ifstream f {"day13.in"};
    string s;
    ll ans = 0;
    
    // x, y target values
    // button A: press a times moves x1 and y1, button b: press b times moves x2 and y2
    // minimize value 3a + b such that a*x1 + b*x2 = x and a*y1 + b*y2 = y

    while (getline(f, s)) {
        string x, y, z;
        getline(f, x); getline(f, y);

        vector<string> a = split(s), b = split(x), c = split(y);
        int x1 = stoi(a[2].substr(2, a[2].length() - 3)), y1 = stoi(a[3].substr(2));
        int x2 = stoi(b[2].substr(2, b[2].length() - 3)), y2 = stoi(b[3].substr(2));
        int tx = stoi(c[1].substr(2, c[1].length() - 3)), ty = stoi(c[2].substr(2));

        int ret = findMin(x1, y1, x2, y2, tx, ty);
        if (ret != -1) {
            ans += ret;
        }
        
        getline(f, s);
    }

    cout << ans << endl;
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
