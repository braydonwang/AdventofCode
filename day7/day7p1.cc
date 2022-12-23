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
    int ans = 0;

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

    for (auto x: map) {
        if (x.second <= 100000) {
            ans += x.second;
        }
    }
    cout << ans << endl;
    
    return 0;
}
