// Q2: Expression Evaluator (C++) - user input
#include <bits/stdc++.h>
using namespace std;
vector<string> tok; int pos;
string pk(){return pos<tok.size()?tok[pos]:"$";}
bool mt(string s){if(pk()==s){pos++;return true;}return false;}
long long E(); long long T(); long long F();
long long E(){ long long v=T(); while(pk()=="+"||pk()=="-"){string o=pk();pos++; if(o=="+")v+=T(); else v-=T();} return v;}
long long T(){ long long v=F(); while(pk()=="*"||pk()=="/"){string o=pk();pos++; if(o=="*")v*=F(); else {long long d=F(); if(d==0) throw runtime_error("division by zero"); v/=d;}} return v;}
long long F(){ if(pk()=="("){mt("("); long long v=E(); if(!mt(")")) throw runtime_error("missing )"); return v;} if(isdigit(pk()[0])|| (pk().size()>1 && pk()[0]=='-' && isdigit(pk()[1]))){ long long v=stoll(pk()); pos++; return v;} throw runtime_error(string("bad token: ")+pk()); }
int main(){
    cout<<"Q2: Expression Evaluator\nEnter arithmetic expression tokens (space-separated), e.g.:\n( 2 + 3 ) * 4 - 6 / 2\n\nInput: ";
    string input; getline(cin,input);
    stringstream ss(input); string x; tok.clear();
    while(ss>>x) tok.push_back(x);
    pos=0;
    try{
        long long res = E();
        if(pos!=tok.size()) throw runtime_error("extra tokens after parsing");
        cout<<"\nResult = "<<res<<"\n";
    }catch(exception &e){
        cout<<"\nError: "<<e.what()<<"\n";
    }
    return 0;
}