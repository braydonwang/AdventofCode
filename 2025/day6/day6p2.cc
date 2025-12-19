#include <bits/stdc++.h>
using ll = long long;

int main() {
    ifstream f {"day6.in"};
    string s;
    vector<string> input;
    int maxlen = 0;

    while (getline(f, s)) {
        if (s.empty()) break;
        input.push_back(s);
        maxlen = max(maxlen, (int)s.length());
    }

    ll sum = 0;
    vector<ll> nums;

    for (int i = maxlen-1; i >= 0; i--) {
        ll num = 0;
        char op = ' ';
        for (int j = 0; j < input.size(); j++) {
            if (input[j].size() <= i || input[j][i] == ' ') continue;
            if (input[j][i] == '+' || input[j][i] == '*') {
                op = input[j][i];
                i--;
            } else {
                num = num * 10 + input[j][i] - '0';
            }
        }

        nums.push_back(num);

        if (op != ' ') {
            if (nums.empty()) continue;
            ll total = nums[0];
            for (int k = 1; k < nums.size(); k++) {
                if (op == '*') {
                    total *= nums[k];
                } else {
                    total += nums[k];
                }
            }
            sum += total;
            nums.clear();
        }
    }

    cout << sum << endl;
}
