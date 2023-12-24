#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <unordered_map>
#include <regex>
#include <string>

using namespace std;
#define ll long long

vector<string> split(string s);

bool check(vector<int> &nums) {
    for (int num: nums) {
        if (num != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream f {"day9.in"};
    string s;
    int sum = 0;

    while (getline(f,s)) {
        vector<string> vec = split(s);
        vector<int> nums;
        for (string str: vec) {
            nums.push_back(stoi(str));
        }
        vector<vector<int>> seq;
        seq.push_back(nums);
        while (!check(nums)) {
            vector<int> temp;
            for (int i = 1; i < nums.size(); i++) {
                temp.push_back(nums[i] - nums[i-1]);
            }
            seq.push_back(temp);
            nums = temp;
        }

        int val = 0;
        for (int i = seq.size() - 2; i >= 0; i--) {
            vector<int> line = seq[i];
            val = line[0] - val;
        }

        sum += val;
    }
    
    cout << sum << endl;

    return 0;
}

vector<string> split(string s) {
    stringstream ss(s);
    string str;
    vector<string> vec;

    while (ss >> str) {
        vec.push_back(str);
    }
    return vec;
}
