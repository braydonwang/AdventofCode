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
        
        ans += num / 100;
        num %= 100;

        if (ch == 'L') {
            pos -= num;
            if (pos <= 0 && pos + num != 0) {
                ans++;
            }
            pos = (pos + 100) % 100;
        } else {
            pos += num;
            if (pos >= 100) {
                ans++;
                pos -= 100;
            }
        }
    }

    cout << ans << endl;
}
