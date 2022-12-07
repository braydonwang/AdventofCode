#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
using namespace std;

int main() {
    ifstream f {"day7.in"};
    string s;
    stack<string> st;
    map<string,long> map;
    int ans = 1e9;

    while (getline(f,s)) {
        istringstream iss{s};
        string a;
        iss >> a;

        if (a == "$") {
            string b;
            iss >> b;
            if (b == "ls") {
                continue;
            } else {
                string c;
                iss >> c;
                if (c == "..") {
                    st.pop();
                } else if (c == "/") {
                    st = stack<string>();
                    st.push("/");
                } else {
                    st.push(st.top()+"/"+c);
                }
            }
        }

        if (a == "dir") {
            continue;
        }
        istringstream tmp{a};
        int num;
        tmp >> num;

        stack<string> temp = st;
        while (!temp.empty()) {
            map[temp.top()] += num;
            temp.pop();
        }
    }

    int diff = 70000000 - map["/"];
    diff = 30000000 - diff;

    for (auto x: map) {
        if (x.second >= diff) {
            if (x.second < ans) {
                ans = x.second;
            }
        }
    }
    cout << ans << endl;
    
    return 0;
}
