#include <iostream>
#include <fstream>
#include <map>
using namespace std;

int main() {
    ifstream f{"day2.in"};
    string c;
    int score = 0;
    map<char,int> points = {{'X',0}, {'Y',3}, {'Z',6}, {'A',1}, {'B',2}, {'C',3}};
    while (f >> c) {
        string d;
        f >> d;
        char a = c[0], b = d[0];
        score += points[b];
        if (b == 'Y') {
            score += points[a];
        } else if (b == 'Z') {
            int temp = (a - 'A' + 1) % 3 + 'A';
            score += points[temp];
        } else {
            int temp = (a - 'A' - 1 + 3) % 3 + 'A';
            score += points[temp];
        }
    }

    cout << score << endl;
    return 0;
}
