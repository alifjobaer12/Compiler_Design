// Q3: Remove Immediate Left Recursion (C++) - user input
#include <bits/stdc++.h>
using namespace std;
int main(){
    cout<<"Q3: Remove Immediate Left Recursion\nEnter grammar productions one per line in format:\nA -> A a | b\nEnter a blank line to finish.\n\n";
    map<string, vector<string>> G;
    string line;
    while(true){
        cout<<"> ";
        if(!std::getline(cin, line)) break;
        if(line.size()==0) break;
        // parse LHS -> RHS
        auto pos = line.find("->");
        if(pos==string::npos){ cout<<"Invalid. Use 'A -> ...' format\n"; continue; }
        string lhs = line.substr(0,pos); string rhs = line.substr(pos+2);
        // trim
        auto trim = [](string s){ while(!s.empty() && isspace((unsigned char)s.front())) s.erase(s.begin()); while(!s.empty() && isspace((unsigned char)s.back())) s.pop_back(); return s; };
        lhs = trim(lhs); rhs = trim(rhs);
        // split productions by '|'
        stringstream ss(rhs); string prod; vector<string> prods;
        // custom split by '|'
        size_t start=0;
        while(start<rhs.size()){
            size_t pipe = rhs.find('|', start);
            string part = (pipe==string::npos)? rhs.substr(start) : rhs.substr(start, pipe-start);
            prods.push_back(trim(part));
            if(pipe==string::npos) break;
            start = pipe+1;
        }
        for(auto &p:prods) G[lhs].push_back(p);
    }
    cout<<"\nOriginal grammar:\n";
    for(auto &kv:G){
        cout<<kv.first<<" -> ";
        for(size_t i=0;i<kv.second.size();++i){ if(i) cout<<" | "; cout<<kv.second[i]; }
        cout<<"\n";
    }
    cout<<"\nAfter removing immediate left recursion where present:\n";
    for(auto &kv:G){
        string A = kv.first;
        vector<string> alpha, beta;
        for(auto &prod: kv.second){
            // split first token
            stringstream ss(prod); string first; ss>>first;
            if(first==A){
                string rest; getline(ss, rest); if(rest.size() && rest[0]==' ') rest = rest.substr(1);
                alpha.push_back(rest);
            } else beta.push_back(prod);
        }
        if(!alpha.empty()){
            string Aprime = A + "'";
            cout<<A<<" -> ";
            for(size_t i=0;i<beta.size();++i){ if(i) cout<<" | "; cout<<beta[i]<<" "<<Aprime; }
            cout<<"\n"<<Aprime<<" -> ";
            for(size_t i=0;i<alpha.size();++i){ if(i) cout<<" | "; cout<<alpha[i]<<" "<<Aprime; }
            cout<<" | epsilon\n";
        } else {
            cout<<A<<" -> ";
            for(size_t i=0;i<kv.second.size();++i){ if(i) cout<<" | "; cout<<kv.second[i]; }
            cout<<"\n";
        }
    }
    return 0;
}