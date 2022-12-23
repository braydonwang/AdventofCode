#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
using namespace std;

void check(int cycle, int x) {
    int pos = (cycle - 1) % 40;
    if (pos >= x - 1 && pos <= x + 1) {
        cout << "#";
    } else {
        cout << ".";
    }
    if (pos == 39) {
        cout << endl;
    }
}

int main() {
    ifstream f {"day10.in"};
    string s;
    int cycle = 1;
    int x = 1;

    while (f >> s) {
        if (s == "noop") {
            check(cycle,x);
            cycle++;
        } else {
            int num;
            f >> num;
            check(cycle,x);
            cycle++;
            check(cycle,x);
            cycle++;
            x += num;
        }
    }

    return 0;
}
