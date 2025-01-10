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

vector<int> split(string s, char delim);
ll ans = -1;

int run(ll a) {
    ll b, c;
    b = a % 8;
    b = b ^ 2;
    c = a >> b;
    b = b ^ c;
    b = b ^ 7;
    return b % 8;
}

void find(int ind, vector<int> &ops, ll a) {
    if (ans != -1) return;
    if (ind == ops.size()) {
        ans = a;
        return;
    }

    a <<= 3;
    for (int i = 0; i < 8; i++) {
        ll na = a + i;
        if (run(na) == ops[ind]) {
            find(ind+1, ops, na);
        }
    }
}

int main() {
    ifstream f {"day17.in"};
    string s;

    getline(f, s); getline(f, s); getline(f, s); getline(f, s); getline(f, s);
    int idx = s.find(':');

    s = s.substr(idx+2);
    vector<int> ops = split(s, ',');
    reverse(ops.begin(), ops.end());

    find(0, ops, 0);

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
