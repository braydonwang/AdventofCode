#include <bits/stdc++.h>
using ll = long long;

int main() {
    ifstream f {"day1.in"};
    string s;
    int pos = 50, ans = 0;

    while (getline(f, s)) {
        if (s.empty()) break;
        char ch = s[0];
        int num = stoi(s.substr(1));
        
        if (ch == 'L') {
            pos = (pos - num + 100) % 100;
        } else {
            pos = (pos + num) % 100;
        }

        if (pos == 0) {
            ans++;
        }
    }

    cout << ans << endl;
}
