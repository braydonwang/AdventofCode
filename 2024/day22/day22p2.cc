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
    vector<int> sums(19 * 19 * 19 * 19);
    vector<bool> seen(19 * 19 * 19 * 19);
    vector<int> vis;

    while (getline(f, s)) {
        ll num = stoll(s);
        int seq = 0, prev = num % 10;

        for (int i = 0; i < 2000; i++) {
            num = prune(mix(num, num * 64));
            num = prune(mix(num, num / 32));
            num = prune(mix(num, num * 2048));

            int diff = num % 10 - prev;
            seq = (seq % (19 * 19 * 19)) * 19 + (diff + 9);
            if (i >= 3 && !seen[seq]) {
                seen[seq] = true;
                vis.push_back(seq);
                sums[seq] += num % 10;
            }
            
            prev = num % 10;
        }

        for (int v: vis) {
            seen[v] = false;
        }
        vis.clear();
    }

    cout << *max_element(sums.begin(), sums.end()) << endl;
}
