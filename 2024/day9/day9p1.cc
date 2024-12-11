#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <regex>

using ll = long long;
using namespace std;

ll asum(int pos, int len) {
    return (2 * pos + len - 1) * len / 2;
}

int main() {
    ifstream f {"day9.in"};
    string s;
    getline(f, s);

    vector<int> blocks, frees;

    for (int i = 0; i < s.length(); i++) {
        int num = s[i] - '0';
        if (i % 2 == 0) {
            blocks.push_back(num);
        } else {
            frees.push_back(num);
        }
    }

    int fi = 0, l = 0, r = blocks.size() - 1;
    int pos = 0;
    ll sum = 0;

    while (l <= r) {
        sum += asum(pos, blocks[l]) * l;
        pos += blocks[l];
        l++;

        if (fi < frees.size()) {
            while (frees[fi] > 0 && l <= r) {
                int mn = min(frees[fi], blocks[r]);
                sum += asum(pos, mn) * r;
                pos += mn;

                frees[fi] -= mn;
                blocks[r] -= mn;
                if (blocks[r] == 0) r--;
            }
            fi++;
        }
    }

    cout << sum << endl;
}
