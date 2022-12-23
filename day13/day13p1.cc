#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <queue>
using namespace std;

#include "packet.h"
#include "integer.h"
#include "list.h"

Packet *parse(string s) {
    if (s[0] >= '0' && s[0] <= '9') {
        return new Integer(stoi(s));
    } else {
        List *lst = new List();
        int sind = 1, eind = 1;
        while (s[eind] != ']') {
            int count = 0;
            while ((s[eind] != ',' && s[eind] != ']') || count != 0) {
                if (s[eind] == '[') {
                    count++;
                } else if (s[eind] == ']') {
                    count--;
                }
                eind++;
            }
            Packet *p = parse(s.substr(sind,eind-sind));
            lst->vec.push_back(p);
            if (s[eind] == ',') {
                eind++;
                sind = eind;
            }
        }
        return lst;
    }
}

int main() {
    ifstream f {"day13.in"};
    string s1, s2;
    int ans = 0;

    int ind = 1;

    while (f >> s1) {
        f >> s2;
        Packet *p1 = parse(s1);
        Packet *p2 = parse(s2);
        int num;
        if (dynamic_cast<Integer *>(p2)) {
            num = p1->compare(dynamic_cast<Integer *>(p2));
        } else {
            num = p1->compare(dynamic_cast<List *>(p2));
        }
        if (num == 1) {
            ans += ind;
        }
        ind++;
    }

    cout << ans << endl;

    return 0;
}
