// Q6: Recursive Descent Parser (C++) - accepts "ep" as epsilon token
// Grammar:
//   E  → T E'
//   E' → + T E' | ep
//   T  → F T'
//   T' → * F T' | ep
//   F  → ( E ) | id
//
// Input tokens are space-separated. You may include "ep" in the input to represent ε.
//
// Example input:
//   ( id + id ) * id
//   id + ep
//   ( id ep )   <-- (not meaningful but parser will consume ep where expected)

#include <bits/stdc++.h>
using namespace std;

string pk(const vector<string>& t, int p){ return p < (int)t.size() ? t[p] : "$"; }
bool mt(const vector<string>& t, int &p, const string &s){
    if(pk(t,p) == s){ p++; return true; }
    return false;
}

// Forward declarations
bool E(const vector<string>&, int&);
bool E_(const vector<string>&, int&);
bool T(const vector<string>&, int&);
bool T_(const vector<string>&, int&);
bool F(const vector<string>&, int&);

// F -> ( E ) | id
bool F(const vector<string>& tokens, int &p){
    if(pk(tokens,p) == "("){
        if(!mt(tokens,p,"(")) return false;
        if(!E(tokens,p)) return false;
        if(!mt(tokens,p,")")) return false;
        return true;
    }
    if(pk(tokens,p) == "id"){
        mt(tokens,p,"id");
        return true;
    }
    return false;
}

// T' -> * F T' | ep
bool T_(const vector<string>& tokens, int &p){
    // If literal "ep" is provided in input, consume it and treat as epsilon.
    if(pk(tokens,p) == "ep"){
        mt(tokens,p,"ep");
        return true; // consumed ep -> epsilon
    }
    if(pk(tokens,p) == "*"){
        mt(tokens,p,"*");
        if(!F(tokens,p)) return false;
        return T_(tokens,p);
    }
    // epsilon (nothing to consume)
    return true;
}

// T -> F T'
bool T(const vector<string>& tokens, int &p){
    if(!F(tokens,p)) return false;
    return T_(tokens,p);
}

// E' -> + T E' | ep
bool E_(const vector<string>& tokens, int &p){
    // If literal "ep" is provided in input, consume it and treat as epsilon.
    if(pk(tokens,p) == "ep"){
        mt(tokens,p,"ep");
        return true;
    }
    if(pk(tokens,p) == "+"){
        mt(tokens,p,"+");
        if(!T(tokens,p)) return false;
        return E_(tokens,p);
    }
    // epsilon (nothing to consume)
    return true;
}

// E -> T E'
bool E(const vector<string>& tokens, int &p){
    if(!T(tokens,p)) return false;
    return E_(tokens,p);
}

int main(){
    cout << "Enter expression tokens (space-separated), e.g.: ( id + id ) * id\n";

    string line;
    if(!std::getline(cin, line)) return 0;
    stringstream ss(line);
    vector<string> tokens;
    string tok;
    while(ss >> tok) tokens.push_back(tok);

    int pos = 0;
    bool ok = E(tokens, pos) && pos == (int)tokens.size();

    cout << "\nResult: " << (ok ? "accepted" : "rejected") << "\n";
    return 0;
}
