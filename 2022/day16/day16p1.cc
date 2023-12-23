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

int main() {
    ifstream f {"day16.in"};
    string s;
    int ans = 0;
    map<string,vector<string>> adj;
    map<string,int> rate;

    while (getline(f,s)) {
        istringstream iss{s};
        iss >> s; iss >> s;
        string valve = s;
        iss >> s; iss >> s; iss >> s;
        int r = stoi(s.substr(5,s.length()-6));
    }

    cout << ans << endl;

    return 0;
}
