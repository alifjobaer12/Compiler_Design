#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> firstSet, followSet;
set<char> nonTerminals;
char startSymbol;

// Function to compute FIRST set
void findFirst(char c) {
    // If already calculated, return
    if (!firstSet[c].empty()) return;

    for (string rule : grammar[c]) {
        if (isupper(rule[0])) { 
            // Non-terminal
            findFirst(rule[0]);
            for (char f : firstSet[rule[0]])
                if (f != '#') firstSet[c].insert(f);

            // If epsilon in FIRST of next non-terminal, check next symbol
            int i = 0;
            while (i < rule.size() && isupper(rule[i]) && firstSet[rule[i]].count('#')) {
                i++;
                if (i < rule.size()) {
                    if (isupper(rule[i])) {
                        findFirst(rule[i]);
                        for (char f : firstSet[rule[i]])
                            if (f != '#') firstSet[c].insert(f);
                    } else {
                        firstSet[c].insert(rule[i]);
                    }
                } else {
                    firstSet[c].insert('#');
                }
            }
        } 
        else if (rule[0] == '#') {
            firstSet[c].insert('#');
        } 
        else {
            // Terminal
            firstSet[c].insert(rule[0]);
        }
    }
}

// Function to compute FOLLOW set
void findFollow(char c) {
    for (auto &p : grammar) {
        char lhs = p.first;
        for (string rule : p.second) {
            for (int i = 0; i < rule.size(); i++) {
                if (rule[i] == c) {
                    if (i + 1 < rule.size()) {
                        if (isupper(rule[i + 1])) {
                            // Add FIRST of next non-terminal
                            for (char f : firstSet[rule[i + 1]]) {
                                if (f != '#') followSet[c].insert(f);
                            }

                            // If epsilon in FIRST(next), add FOLLOW(lhs)
                            if (firstSet[rule[i + 1]].count('#')) {
                                findFollow(lhs);
                                for (char f : followSet[lhs])
                                    followSet[c].insert(f);
                            }
                        } else {
                            // Next is terminal
                            followSet[c].insert(rule[i + 1]);
                        }
                    } else if (lhs != c) {
                        // End of rule, add FOLLOW(lhs)
                        findFollow(lhs);
                        for (char f : followSet[lhs])
                            followSet[c].insert(f);
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions (like E=TA or A=+TA|#):\n";
    for (int i = 0; i < n; i++) {
        string input;
        cin >> input;
        char lhs = input[0];
        if (i == 0) startSymbol = lhs; // first production is start symbol
        string rhs = input.substr(2);

        string temp = "";
        for (char c : rhs) {
            if (c == '|') {
                grammar[lhs].push_back(temp);
                temp = "";
            } else {
                temp += c;
            }
        }
        grammar[lhs].push_back(temp);
        nonTerminals.insert(lhs);
    }

    // Compute FIRST sets
    for (char nt : nonTerminals)
        findFirst(nt);

    // Initialize FOLLOW(start) = $
    followSet[startSymbol].insert('$');

    // Compute FOLLOW sets
    for (char nt : nonTerminals)
        findFollow(nt);

    // Print FIRST sets
    cout << "\nFIRST sets:\n";
    for (auto &p : firstSet) {
        cout << "FIRST(" << p.first << ") = { ";
        for (char c : p.second) cout << c << " ";
        cout << "}\n";
    }

    // Print FOLLOW sets
    cout << "\nFOLLOW sets:\n";
    for (auto &p : followSet) {
        cout << "FOLLOW(" << p.first << ") = { ";
        for (char c : p.second) cout << c << " ";
        cout << "}\n";
    }

    return 0;
}
