#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
using namespace std;

vector<string> parse(string s) {
    istringstream iss{s};
    vector<string> input;
    while (iss >> s) {
        input.push_back(s);
    }
    return input;
}

int main() {
    ifstream f {"day11.in"};
    string s;
    
    vector<vector<int>> item;
    vector<pair<string,string>> operation;
    vector<int> tests;
    vector<pair<int,int>> cond;
    vector<int> count(8,0);

    for (int i = 0; i < 8; i++) {
        item.emplace_back(vector<int>());
    }

    for (int i = 0; i < 8; i++) {
        getline(f,s);
        getline(f,s);
        vector<string> start = parse(s);
        getline(f,s);
        vector<string> op = parse(s);
        getline(f,s);
        vector<string> test = parse(s);
        getline(f,s);
        vector<string> tr = parse(s);
        getline(f,s);
        vector<string> fa = parse(s);
        for (int j = 2; j < start.size(); j++) {
            string str = start[j];
            if (str[str.length()-1] == ',') {
                str = str.substr(0,str.length()-1);
            }
            item[i].emplace_back(stoi(str));
        }
        operation.push_back({op[4],op[5]});
        tests.push_back(stoi(test[3]));
        cond.push_back({stoi(tr[5]),stoi(fa[5])});
        getline(f,s);
    }

    // for (int i = 0; i < 8; i++) {
    //     cout << "Monkey " << i << ": ";
    //     for (int num: item[i]) {
    //         cout << num << " ";
    //     }
    //     cout << operation[i].first << " " << operation[i].second << " ";
    //     cout << tests[i] << " ";
    //     cout << cond[i].first << " " << cond[i].second << endl;
    // }

    int num = 20;
    while (num-- > 0) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < item[i].size(); j++) {
                count[i]++;
                int newItem = 0;
                if (operation[i].first == "+") {
                    newItem = item[i][j] + stoi(operation[i].second);
                } else {
                    if (operation[i].second[0] == 'o') {
                        newItem = item[i][j] * item[i][j];
                    } else {
                        newItem = item[i][j] * stoi(operation[i].second);
                    }
                }
                newItem /= 3;
                if (newItem % tests[i] == 0) {
                    item[cond[i].first].push_back(newItem);
                } else {
                    item[cond[i].second].push_back(newItem);
                }
            }
            item[i].clear();
        }
    }

    sort(count.begin(),count.end(),greater<int>());

    cout << count[0] * count[1] << endl;

    return 0;
}
