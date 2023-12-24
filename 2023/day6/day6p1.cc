#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <unordered_map>
#include <regex>
#include <string>

using namespace std;
vector<string> split(string s);

int calc(int hold, int time) {
    return (time - hold) * hold;
}

int main() {
    ifstream f {"day6.in"};
    string s;
    long prod = 1;

    getline(f,s);
    vector<string> vec = split(s);
    vector<int> time;
    for (int i = 1; i < vec.size(); i++) {
        time.push_back(stoi(vec[i]));
    }

    getline(f,s);
    vec = split(s);
    vector<int> dist;
    for (int i = 1; i < vec.size(); i++) {
        dist.push_back(stoi(vec[i]));
    }

    for (int i = 0; i < time.size(); i++) {
        int lo = 0, hi = time[i];
        int l = 0, r = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int travel = calc(mid, time[i]);
            if (travel > dist[i]) {
                l = mid;
                hi = mid - 1;
            } else {
                if (calc(mid + 1, time[i]) >= travel) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
        }

        lo = 0; hi = time[i];
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int travel = calc(mid, time[i]);
            if (travel > dist[i]) {
                r = mid;
                lo = mid + 1;
            } else {
                if (calc(mid + 1, time[i]) >= travel) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
        }
        prod *= (r - l + 1);
    }
    
    cout << prod << endl;

    return 0;
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
