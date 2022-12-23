#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    ifstream f {"day1.in"};
    string s;
    int a = 0, b = 0, c = 0;
    int sum = 0;
    while (getline(f,s)) {
        istringstream iss{s};
        int num;
        if (iss >> num) {
            sum += num;
        } else {
            if (sum >= a) {
                c = b;
                b = a;
                a = sum;
            } else if (sum >= b) {
                c = b;
                b = sum;
            } else if (sum >= c) {
                c = sum;
            }
            sum = 0;
        }
    }
    cout << a + b + c << endl;
    return 0;
}
