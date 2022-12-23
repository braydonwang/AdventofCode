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
    string s1;

    List *a = new List;
    List *b = new List;
    b->vec.push_back(new Integer(2));
    a->vec.push_back(b);

    List *c = new List;
    List *d = new List;
    d->vec.push_back(new Integer(6));
    c->vec.push_back(d);

    int l1 = 0, l2 = 0;

    while (f >> s1) {
        Packet *p1 = parse(s1);
        int num1, num2;
        if (dynamic_cast<Integer *>(p1)) {
            num1 = a->compare(dynamic_cast<Integer *>(p1));
            num2 = c->compare(dynamic_cast<Integer *>(p1));
        } else {
            num1 = a->compare(dynamic_cast<List *>(p1));
            num2 = c->compare(dynamic_cast<List *>(p1));
        }
        if (num1 == 2) {
            l1++;
        }
        if (num2 == 2) {
            l2++;
        }
    }

    cout << (l1 + 1) * (l2 + 2) << endl;

    return 0;
}
