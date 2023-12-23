#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <regex>

using namespace std;

int main() {
    ifstream f {"day1.in"};
    string s;
    int sum = 0;
    vector<string> nums = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    while (getline(f,s)) {
        int start = -1, end = -1;

        int i = 0;
        while (i < s.length()) {
            char ch = s[i];
            int num = -1;

            if (ch >= '0' && ch <= '9') {
                num = ch - '0';
            } else {
                for (int j = 0; j < nums.size(); j++) {
                    if (s.length() - i >= nums[j].length() && s.substr(i,nums[j].length()) == nums[j]) {
                        num = j + 1;
                        break;
                    }
                }
            }

            if (num != -1) {
                start = num;
                break;
            }
            i++;
        }

        i = s.length() - 1;
        while (i >= 0) {
            char ch = s[i];
            int num = -1;

            if (ch >= '0' && ch <= '9') {
                num = ch - '0';
            } else {
                for (int j = 0; j < nums.size(); j++) {
                    if (s.length() - i >= nums[j].length() && s.substr(i,nums[j].length()) == nums[j]) {
                        num = j + 1;
                        break;
                    }
                }
            }

            if (num != -1) {
                end = num;
                break;
            }
            i--;
        }

        sum += 10 * start + end;
    }

    cout << sum << endl;
    return 0;
}
