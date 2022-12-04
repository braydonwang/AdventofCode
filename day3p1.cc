#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

bool contains(string s, char ch) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ch) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream f {"day3.in"};
    string s;
    int ans = 0;

    while (f >> s) {
        int length = s.length() / 2;
        string s1 = s.substr(0,length), s2 = s.substr(length,length);
        for (char ch = 'a'; ch <= 'z'; ch++) {
            char up = 'A' - 'a' + ch;
            if (contains(s1,ch) && contains(s2,ch)) {
                ans += ch - 'a' + 1;
                break;
            } else if (contains(s1,up) && contains(s2,up)) {
                ans += up - 'A' + 27;
                break;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
