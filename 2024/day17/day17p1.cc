#include <bits/stdc++.h>

using ll = long long;

/*

0: A = floor(A / 2^combo)
1: B = B XOR literal
2: B = combo % 8
3: if A != 0, jump to literal instruction
4: B = B XOR C
5: output combo % 8
6: B = floor(A / 2^combo)
7: C = floor(A / 2^combo)

*/

ll a, b, c;
vector<int> split(string s, char delim);

ll getReg(ifstream &f) {
    string s;
    getline(f, s);

    int idx = s.find(':');
    return (ll)stoi(s.substr(idx+2));
}

int combo(int s) {
    if (s <= 3) {
        return s;
    } else if (s == 4) {
        return a;
    } else if (s == 5) {
        return b;
    }
    return c;
}

int main() {
    ifstream f {"day17.in"};
    string str;
    
    string ans = "";
    a = getReg(f); b = getReg(f); c = getReg(f);

    getline(f, str); getline(f, str);
    int idx = str.find(':');

    str = str.substr(idx+2);
    vector<int> ops = split(str, ',');

    int ip = 0;
    while (ip < ops.size()) {
        int f = ops[ip], s = ops[ip+1];
        if (f == 0) {
            a = (ll)(a / pow(2, combo(s)));
        } else if (f == 1) {
            b = b ^ s;
        } else if (f == 2) {
            b = combo(s) % 8;
        } else if (f == 3) {
            if (a != 0) {
                ip = s;
                continue;
            }
        } else if (f == 4) {
            b = b ^ c;
        } else if (f == 5) {
            string out = to_string(combo(s) % 8);
            if (!ans.empty()) ans += ',';
            ans += out;
        } else if (f == 6) {
            b = (ll)(a / pow(2, combo(s)));
        } else {
            c = (ll)(a / pow(2, combo(s)));
        }

        ip += 2;
    }

    cout << ans << endl;
}

vector<int> split(string s, char delim) {
    int ind = 0;
    string acc = "";
    vector<int> vec;

    while (ind < s.length()) {
        if (s[ind] == delim) {
            vec.push_back(stoi(acc));
            acc = "";
        } else {
            acc += s[ind];
        }
        ind++;
    }
    vec.push_back(stoi(acc));

    return vec;
}
