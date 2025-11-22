// Q1: Expression Validity Checker (C++)
// Answer: Recursive-descent parser that checks syntax for id,+,-,*,/,() (user input)
#include <bits/stdc++.h>
using namespace std;
string peek(vector<string>& t, int p) { return p < t.size() ? t[p] : "$"; }
bool match(vector<string>& t, int& p, string s){ if (peek(t, p) == s) { p++; return true; } return false; }
bool F(vector<string>&, int&);
bool T(vector<string>&, int&);
bool E(vector<string>&, int&);
bool E_(vector<string>&, int&);
bool T_(vector<string>&, int&);
bool F(vector<string>& t, int& p){
    if (peek(t, p) == "id") { match(t, p, "id"); return true; }
    if (match(t, p, "(")) { if (!E(t, p)) return false; if (!match(t, p, ")")) return false; return true; }
    return false;
}
bool T(vector<string>& t, int& p) { return F(t, p) && T_(t, p); }
bool T_(vector<string>& t, int& p){
    if (peek(t, p) == "*") { match(t, p, "*"); return F(t, p) && T_(t, p); }
    if (peek(t, p) == "/") { match(t, p, "/"); return F(t, p) && T_(t, p); }
    return true;
}
bool E(vector<string>& t, int& p) { return T(t, p) && E_(t, p); }
bool E_(vector<string>& t, int& p){
    if (peek(t, p) == "+") { match(t, p, "+"); return T(t, p) && E_(t, p); }
    if (peek(t, p) == "-") { match(t, p, "-"); return T(t, p) && E_(t, p); }
    return true;
}
int main(){
    cout<<"Q1: Expression Validity Checker\nEnter expression tokens (space-separated), e.g.:\n id + id * ( id - id )\n\nInput: ";
    string input; getline(cin, input);
    stringstream ss(input); vector<string> t; string x;
    while (ss >> x) t.push_back(x);
    int p = 0;
    bool ok = E(t, p) && p == t.size();
    cout << "\nResult: " << (ok ? "accepted" : "rejected") << "\n";
    return 0;
}