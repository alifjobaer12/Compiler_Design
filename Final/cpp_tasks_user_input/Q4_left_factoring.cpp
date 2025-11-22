// Q4: Left Factoring (C++) - user input for one nonterminal
#include <bits/stdc++.h>
using namespace std;
int main(){
    cout<<"Q4: Left Factoring\nEnter a production like: A -> a b | a c | d\n\nInput: ";
    string line; getline(cin,line);
    auto trim = [](string s){ while(!s.empty() && isspace((unsigned char)s.front())) s.erase(s.begin()); while(!s.empty() && isspace((unsigned char)s.back())) s.pop_back(); return s; };
    auto pos = line.find("->");
    if(pos==string::npos){ cout<<"Invalid format\n"; return 0; }
    string A = trim(line.substr(0,pos));
    string rhs = trim(line.substr(pos+2));
    // split alternatives
    vector<string> prods; size_t start=0;
    while(start<rhs.size()){
        size_t pipe = rhs.find('|', start);
        string part = (pipe==string::npos)? rhs.substr(start) : rhs.substr(start, pipe-start);
        prods.push_back(trim(part));
        if(pipe==string::npos) break;
        start = pipe+1;
    }
    // find common prefixes - simple approach: check first token
    map<string, vector<vector<string>>> groups;
    for(auto &p:prods){
        stringstream ss(p); vector<string> tokens; string t;
        while(ss>>t) tokens.push_back(t);
        string key = tokens.size()? tokens[0] : "";
        groups[key].push_back(tokens);
    }
    cout<<"\nAfter left factoring:\n";
    vector<vector<string>> restGroups;
    for(auto &g:groups){
        if(g.second.size()>1 && g.first!=""){
            string Aprime = A + "'" ;
            cout<<A<<" -> "<<g.first<<" "<<Aprime;
            // add other groups with different first tokens as separate alternatives
            for(auto &h:groups){ if(h.first!=g.first){
                for(auto &prod:h.second){ cout<<" | "; for(size_t i=0;i<prod.size();++i){ if(i) cout<<" "; cout<<prod[i]; } }
            }}
            cout<<"\n"<<Aprime<<" -> ";
            for(size_t i=0;i<g.second.size();++i){
                auto tokens = g.second[i];
                if(tokens.size()>1){
                    for(size_t j=1;j<tokens.size();++j){ if(j>1) cout<<" "; cout<<tokens[j]; }
                } else cout<<"epsilon";
                if(i+1<g.second.size()) cout<<" | ";
            }
            cout<<"\n";
            return 0;
        }
    }
    // if no factoring possible, print original
    cout<<A<<" -> ";
    for(size_t i=0;i<prods.size();++i){ if(i) cout<<" | "; cout<<prods[i]; }
    cout<<"\n";
    return 0;
}