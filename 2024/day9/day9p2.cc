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

    vector<pair<int, int>> blocks, frees;
    int pos = 0;

    for (int i = 0; i < s.length(); i++) {
        int num = s[i] - '0';
        if (i % 2 == 0) {
            blocks.push_back({pos, num});
        } else {
            frees.push_back({pos, num});
        }
        pos += num;
    }

    ll sum = 0;

    for (int i = blocks.size() - 1; i >= 0; i--) {
        pair<int,int> block = blocks[i];
        int ind = 0;
        bool added = false;

        while (ind < frees.size() && frees[ind].first < block.first) {
            if (frees[ind].second >= block.second) {
                sum += asum(frees[ind].first, block.second) * i;
                frees[ind].first += block.second;
                frees[ind].second -= block.second;
                added = true;
                break;
            }
            ind++;
        }

        if (!added) {
            sum += asum(block.first, block.second) * i;
        }
    }

    cout << sum << endl;
}
