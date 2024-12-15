#include <bits/stdc++.h>

using ll = long long;
using ld = long double;

vector<string> split(string s);

ll findMin(ll x1, ll y1, ll x2, ll y2, ll tx, ll ty) {
    ll x = tx + 1e13, y = ty + 1e13;
    ll det = x1 * y2 - x2 * y1;

    ll a = x * y2 - y * x2;
    if (a % det != 0) return -1;
    a /= det;
    if (a < 0) return -1;

    ll b = -x * y1 + y * x1;
    if (b % det != 0) return -1;
    b /= det;
    if (b < 0) return -1;

    return 3 * a + b;
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

        ll ret = findMin(x1, y1, x2, y2, tx, ty);
        if (ret != -1) ans += ret;
        
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
