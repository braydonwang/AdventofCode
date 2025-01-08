#include <bits/stdc++.h>

using ll = long long;

const vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};

ll mix(ll secret, ll num) {
    return secret ^ num;
}

ll prune(ll num) {
    return num % 16777216;
}

int main() {
    ifstream f {"day22.in"};
    string s;
    ll ans = 0;

    while (getline(f, s)) {
        ll num = stoll(s);
        int cnt = 2000;
        while (cnt--) {
            num = prune(mix(num, num * 64));
            num = prune(mix(num, num / 32));
            num = prune(mix(num, num * 2048));
        }
        ans += num;
    }

    cout << ans << endl;
}
