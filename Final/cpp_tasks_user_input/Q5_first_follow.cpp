// Q5: FIRST & FOLLOW (C++) - user input grammar
#include <bits/stdc++.h>
using namespace std;
int main(){
    cout<<"Q5: FIRST and FOLLOW sets\nEnter grammar productions one per line (A -> alpha | beta). Blank line to finish.\n\n";
    map<string, vector<vector<string>>> G;
    string line;
    auto trim = [](string s){ while(!s.empty() && isspace((unsigned char)s.front())) s.erase(s.begin()); while(!s.empty() && isspace((unsigned char)s.back())) s.pop_back(); return s; };
    while(true){
        cout<<"> ";
        if(!getline(cin,line)) break;
        if(line.empty()) break;
        auto pos = line.find("->");
        if(pos==string::npos){ cout<<"Invalid format\n"; continue; }
        string L = trim(line.substr(0,pos));
        string rhs = trim(line.substr(pos+2));
        // split by '|'
        size_t start=0;
        while(start<rhs.size()){
            size_t pipe = rhs.find('|', start);
            string part = (pipe==string::npos)? rhs.substr(start) : rhs.substr(start, pipe-start);
            part = trim(part);
            // tokenize
            stringstream ss(part); string tok; vector<string> tokens;
            while(ss>>tok) tokens.push_back(tok);
            G[L].push_back(tokens);
            if(pipe==string::npos) break;
            start = pipe+1;
        }
    }
    if(G.empty()){ cout<<"No grammar entered\n"; return 0; }
    // compute FIRST
    map<string, set<string>> FIRST, FOLLOW;
    function<void(const string&)> compute_first = [&](const string &X){
        if(!G.count(X)) return;
        if(!FIRST[X].empty()) return;
        for(auto &prod: G[X]){
            if(prod.size()==1 && prod[0]=="epsilon") FIRST[X].insert("epsilon");
            else{
                for(auto &sym: prod){
                    if(!G.count(sym)){ FIRST[X].insert(sym); break; }
                    compute_first(sym);
                    for(auto &t: FIRST[sym]) if(t!="epsilon") FIRST[X].insert(t);
                    if(!FIRST[sym].count("epsilon")) break;
                }
            }
        }
    };
    for(auto &p:G) compute_first(p.first);
    // init FOLLOW with start symbol
    string startSym = G.begin()->first;
    FOLLOW[startSym].insert("$");
    bool changed=true;
    while(changed){
        changed=false;
        for(auto &A:G){
            for(auto &prod: A.second){
                for(size_t i=0;i<prod.size();++i){
                    string B = prod[i];
                    if(!G.count(B)) continue;
                    set<string> trailer;
                    if(i+1<prod.size()){
                        for(size_t j=i+1;j<prod.size();++j){
                            string sym = prod[j];
                            if(!G.count(sym)){ trailer.insert(sym); break; }
                            for(auto &t: FIRST[sym]) if(t!="epsilon") trailer.insert(t);
                            if(!FIRST[sym].count("epsilon")) break;
                            if(j==prod.size()-1) for(auto &x: FOLLOW[A.first]) trailer.insert(x);
                        }
                    } else {
                        for(auto &x: FOLLOW[A.first]) trailer.insert(x);
                    }
                    size_t before = FOLLOW[B].size();
                    FOLLOW[B].insert(trailer.begin(), trailer.end());
                    if(FOLLOW[B].size()!=before) changed=true;
                }
            }
        }
    }
    cout<<"\nFIRST sets:\n";
    for(auto &p:FIRST){ cout<<p.first<<" : "; for(auto &t:p.second) cout<<t<<" "; cout<<"\n"; }
    cout<<"\nFOLLOW sets:\n";
    for(auto &p:FOLLOW){ cout<<p.first<<" : "; for(auto &t:p.second) cout<<t<<" "; cout<<"\n"; }
    return 0;
}