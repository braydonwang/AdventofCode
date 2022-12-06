#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
using namespace std;

int main() {
    ifstream f {"day6.in"};
    string s;
    
    f >> s;

    int l = 0, r = 3;
    int unique = 0;
    map<char,int> map;
    for (int i = 0; i <= 3; i++) {
        map[s[i]]++;
        if (map[s[i]] == 1) {
            unique++;
        } 
    }

    while (unique != 4) {
        map[s[l]]--;
        l++;
        if (map[s[l-1]] == 0) {
            unique--;
        }
        r++;
        map[s[r]]++;
        if (map[s[r]] == 1) {
            unique++;
        }
    }

    cout << r + 1 << endl;
    
    return 0;
}
