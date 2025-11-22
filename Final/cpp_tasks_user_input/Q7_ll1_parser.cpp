// Q7: LL(1) Parser Simulation (C++) - pretty formatted output
#include <bits/stdc++.h>
using namespace std;

void printStack(const vector<string>& st){
    for(auto &s : st) cout << s << " ";
}

void printInput(const vector<string>& inp, int ip){
    for(int i = ip; i < inp.size(); i++)
        cout << inp[i] << " ";
}

int main(){
    cout << "Q7: LL(1) Parser Simulation\nEnter token sequence (space-separated), e.g.: id + id * id\n(Automatically appends $)\n\nInput: ";

    string line;
    getline(cin, line);

    stringstream ss(line);
    vector<string> input;
    string tok;

    while (ss >> tok) input.push_back(tok);
    input.push_back("$");

    vector<string> stack = {"$", "E"};
    int ip = 0;

    cout << "\nStack\t\t\tInput\t\t\tAction\n";

    while (!stack.empty()) {
        string top = stack.back();
        string cur = input[ip];

        // Pretty print stack
        printStack(stack);
        cout << "\t\t\t";

        // Pretty print remaining input
        printInput(input, ip);
        cout << "\t\t\t";

        // Accept
        if (top == cur && top == "$") {
            cout << "Accept\n";
            break;
        }

        // Terminal match
        if (top == cur) {
            stack.pop_back();
            ip++;
            cout << "Match " << cur << "\n";
            continue;
        }

        // Nonterminal rules:
        if (top == "E") {
            if (cur == "id" || cur == "(") {
                stack.pop_back();
                stack.push_back("E'");
                stack.push_back("T");
                cout << "E -> T E'\n";
                continue;
            }
        }

        if (top == "E'") {
            if (cur == "+") {
                stack.pop_back();
                stack.push_back("E'");
                stack.push_back("T");
                stack.push_back("+");
                cout << "E' -> + T E'\n";
                continue;
            }
            stack.pop_back();
            cout << "E' -> epsilon\n";
            continue;
        }

        if (top == "T") {
            if (cur == "id" || cur == "(") {
                stack.pop_back();
                stack.push_back("T'");
                stack.push_back("F");
                cout << "T -> F T'\n";
                continue;
            }
        }

        if (top == "T'") {
            if (cur == "*") {
                stack.pop_back();
                stack.push_back("T'");
                stack.push_back("F");
                stack.push_back("*");
                cout << "T' -> * F T'\n";
                continue;
            }
            stack.pop_back();
            cout << "T' -> epsilon\n";
            continue;
        }

        if (top == "F") {
            if (cur == "id") {
                stack.pop_back();
                stack.push_back("id");
                cout << "F -> id\n";
                continue;
            }
            if (cur == "(") {
                stack.pop_back();
                stack.push_back(")");
                stack.push_back("E");
                stack.push_back("(");
                cout << "F -> ( E )\n";
                continue;
            }
        }

        cout << "Error\n";
        break;
    }

    return 0;
}
