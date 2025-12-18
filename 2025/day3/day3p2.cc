#include <bits/stdc++.h>
using ll = long long;

vector<vector<int>> getInds(string s) {
    vector<vector<int>> inds(10);
    for (int i = 0; i < s.length(); i++) {
        int num = s[i] - '0';
        inds[num].push_back(i);
    }
    return inds;
}

string solve(int ind, int digit, vector<vector<int>> &inds) {
    for (int i = 9; i >= 1; i--) {
        auto it = lower_bound(inds[i].begin(), inds[i].end(), ind);
        if (it != inds[i].end()) {
            if (digit == 11) {
                return to_string(i);
            } else {
                int nextInd = *it + 1;
                string next = solve(nextInd, digit + 1, inds);
                if (!next.empty()) {
                    return to_string(i) + next;
                }
            }
        }
    }
    return "";
}

ll bestVal(string s) {
    vector<vector<int>> inds = getInds(s);
    string bestNum = solve(0, 0, inds);
    return stoll(bestNum);
}

int main() {
    ifstream f {"day3.in"};
    string s;
    ll sum = 0;

    while (getline(f, s)) {
        if (s.empty()) break;
        sum += bestVal(s);
    }

    cout << sum << endl;
}
