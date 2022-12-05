#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

stack<char> reverse(stack<char> s) {
    stack<char> ret;
    while (!s.empty()) {
        ret.push(s.top());
        s.pop();
    }
    return ret;
}

int main() {
    ifstream f {"day5.in"};
    string s;
    vector<stack<char>> vec;
    for (int i = 0; i < 9; i++) {
        vec.push_back(stack<char>());
    }
    string ans = "";
    int ind = 0;
    while (f >> s) {
        if (s == "done") {
            break;
        }
        if (s != ".") {
            vec[ind].push(s[1]);
        }
        ind = (ind + 1) % 9;
    }

    for (int i = 0; i < vec.size(); i++) {
        vec[i] = reverse(vec[i]);
    }

    while (f >> s) {
        int num, a, b;
        f >> num;
        f >> s;
        f >> a;
        f >> s;
        f >> b;
        a--; b--;
        stack<char> temp;
        for (int i = 0; i < num; i++) {
            temp.push(vec[a].top());
            vec[a].pop();
        }
        for (int i = 0; i < num; i++) {
            vec[b].push(temp.top());
            temp.pop();
        }
    }

    for (int i = 0; i < 9; i++) {
        ans += vec[i].top();
    }

    cout << ans << endl;
    return 0;
}
