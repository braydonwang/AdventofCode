#include <bits/stdc++.h>

using ll = long long;

unordered_map<string, vector<string>> forms;
vector<string> split(string &s);
bool verifyCarry(string wire, int num);

string make(char ch, int num) {
    string ret = to_string(num);
    if (ret.size() == 1) ret = "0" + ret;
    return ch + ret;
}

bool verifyPair(string a, string b, int num) {
    return (a == make('x', num) && b == make('y', num)) || (b == make('x', num) && a == make('y', num));
}

bool verifyXOR(string wire, int num) {
    if (!forms.contains(wire)) return false;
    string a = forms[wire][0], op = forms[wire][1], b = forms[wire][2];
    if (op != "XOR") return false;
    return verifyPair(a, b, num);
}

bool verifyDirectCarry(string wire, int num) {
    if (!forms.contains(wire)) return false;
    string a = forms[wire][0], op = forms[wire][1], b = forms[wire][2];
    if (op != "AND") return false;
    return verifyPair(a, b, num);
}

bool verifyRecarry(string wire, int num) {
    if (!forms.contains(wire)) return false;
    string a = forms[wire][0], op = forms[wire][1], b = forms[wire][2];
    if (op != "AND") return false;
    return (verifyXOR(a, num) && verifyCarry(b, num)) || (verifyXOR(b, num) && verifyCarry(a, num));
}

bool verifyCarry(string wire, int num) {
    if (!forms.contains(wire)) return false;
    string a = forms[wire][0], op = forms[wire][1], b = forms[wire][2];
    if (num == 1) {
        if (op != "AND") return false;
        return verifyPair(a, b, 0);
    }
    if (op != "OR") return false;
    return (verifyDirectCarry(a, num-1) && verifyRecarry(b, num-1)) || (verifyDirectCarry(b, num-1) && verifyRecarry(a, num-1));
}

bool verifyZ(string wire, int num) {
    if (!forms.contains(wire)) return false;
    string a = forms[wire][0], op = forms[wire][1], b = forms[wire][2];
    if (op != "XOR") return false;
    if (num == 0) return verifyPair(a, b, 0);
    return (verifyXOR(a, num) && verifyCarry(b, num)) || (verifyXOR(b, num) && verifyCarry(a, num));
}

bool verify(int ind) {
    return verifyZ(make('z', ind), ind);
}

int check(int ind) {
    while (true) {
        if (!verify(ind)) {
            break;
        }
        ind++;
    }

    return ind;
}

int main() {
    ifstream f {"day24.in"};
    string s;

    while (getline(f, s)) {
        if (s.empty()) break;
    }

    while (getline(f, s)) {
        vector<string> vec = split(s);
        string na = vec[0], op = vec[1], nb = vec[2], nc = vec[4];
        forms[nc] = {na, op, nb};
    }

    int cnt = 4, ind = 0;
    vector<string> swaps;

    while (cnt--) {
        int base = check(ind);
        for (auto &[a, _]: forms) {
            for (auto &[b, _]: forms) {
                if (a == b) continue;
                swap(forms[a], forms[b]);

                int tmp = check(ind);
                if (tmp > base) {
                    ind = tmp;
                    swaps.push_back(a); swaps.push_back(b);
                    goto end;
                }
                swap(forms[a], forms[b]);
            }
        }
        end: ;
    }

    sort(swaps.begin(), swaps.end());

    string ans = "";
    for (string str: swaps) {
        if (!ans.empty()) ans += ',';
        ans += str;
    }

    cout << ans << endl;
}

vector<string> split(string &s) {
    vector<string> ret;
    int ind = 0;
    string acc = "";

    while (ind < s.length()) {
        if (s[ind] == ' ') {
            ret.push_back(acc);
            acc = "";
        } else {
            acc += s[ind];
        }
        ind++;
    }

    ret.push_back(acc);
    return ret;
}
