#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
using namespace std;

void check(int cycle, int x, int &ans) {
    if (cycle <= 220 && cycle % 40 == 20) {
        ans += x * cycle;
    }
}

int main() {
    ifstream f {"day10.in"};
    string s;
    int ans = 0;
    int cycle = 1;
    int x = 1;

    while (f >> s) {
        if (s == "noop") {
            check(cycle,x,ans);
            cycle++;
        } else {
            int num;
            f >> num;
            check(cycle,x,ans);
            cycle++;
            check(cycle,x,ans);
            cycle++;
            x += num;
        }
    }

    cout << ans << endl;
    return 0;
}
