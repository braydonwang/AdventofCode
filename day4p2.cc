#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int getDigit(string s, int *ind) {
    int num = 0;
    while (s[*ind] >= '0' && s[*ind] <= '9') {
        num = num * 10 + s[*ind] - '0';
        (*ind)++;
    }
    return num;
}

int main() {
    ifstream f {"day4.in"};
    string s;
    int ans = 0;
    while (f >> s) {
        int ind = 0;
        int a = getDigit(s,&ind);
        ind++;
        int b = getDigit(s,&ind);
        ind++;
        int c = getDigit(s,&ind);
        ind++;
        int d = getDigit(s,&ind);
        if (!(b < c || a > d)) {
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}
