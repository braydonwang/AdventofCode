#include <bits/stdc++.h>
using ll = long long;

int main() {
    ifstream f {"day3.in"};
    string s;
    int sum = 0;

    while (getline(f, s)) {
        if (s.empty()) break;
        vector<int> left(10, -1), right(10, -1);
        for (int i = 0; i < s.length(); i++) {
            int num = s[i] - '0';
            if (left[num] == -1) left[num] = i;
            right[num] = i;
        }

        for (int l = 9; l >= 1; l--) {
            if (left[l] == -1) continue;
            for (int r = 9; r >= 1; r--) {
                if (left[l] < right[r]) {
                    sum += l * 10 + r;
                    goto end;
                }
            }
        }
        end:
    }

    cout << sum << endl;
}
