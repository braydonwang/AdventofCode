#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
using namespace std;

int main() {
    ifstream f {"day8.in"};
    string s;

    int ans = 0;
    int col = 0;
    int row = 0;
    vector<vector<int>> grid;
    vector<string> vec;

    while (f >> s) {
        col = s.length();
        row++;
        vec.push_back(s);
    }

    for (int i = 0; i < row; i++) {
        vector<int> temp;
        for (int j = 0; j < col; j++) {
            temp.push_back(vec[i][j] - '0');
        }
        grid.push_back(temp);
    }

    ans = 2 * row + 2 * (col - 2);

    for (int i = 1; i < row - 1; i++) {
        for (int j = 1; j < row - 1; j++) {
            int visible = 4;
            for (int k = j + 1; k < col; k++) {
                if (grid[i][k] >= grid[i][j]) {
                    visible--;
                    break;
                }
            }
            for (int k = j - 1; k >= 0; k--) {
                if (grid[i][k] >= grid[i][j]) {
                    visible--; 
                    break;
                }
            }
            for (int k = i + 1; k < row; k++) {
                if (grid[k][j] >= grid[i][j]) {
                    visible--;
                    break;
                }
            }
            for (int k = i - 1; k >= 0; k--) {
                if (grid[k][j] >= grid[i][j]) {
                    visible--;
                    break;
                }
            }
            if (visible > 0) {
                ans++;
            }
        }
    }

    cout << ans << endl;
    
    return 0;
}
