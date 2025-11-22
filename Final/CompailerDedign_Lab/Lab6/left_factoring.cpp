#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

// Function to find common prefix between two strings
string commonPrefix(const string &a, const string &b) {
    string prefix = "";
    for (int i = 0; i < min(a.size(), b.size()); i++) {
        if (a[i] == b[i])
            prefix += a[i];
        else
            break;
    }
    return prefix;
}

int main() {
    string input;
    cout << "Enter grammar (example: A=abC|abD|aE): ";
    cin >> input;

    // Split left and right parts
    size_t eqPos = input.find("=");
    string left = input.substr(0, eqPos);
    string right = input.substr(eqPos + 1);

    // Split alternatives
    vector<string> prods;
    stringstream ss(right);
    string temp;
    while (getline(ss, temp, '|'))
        prods.push_back(temp);

    // Find common prefix
    string prefix = prods[0];
    for (int i = 1; i < prods.size(); i++)
        prefix = commonPrefix(prefix, prods[i]);

    if (prefix.empty()) {
        cout << "\nNo left factoring needed.\n";
    } else {
        cout << "\nLeft factoring possible!\n";
        cout << "Common prefix: " << prefix << endl;

        // Create new productions
        string newNonTerminal = left + "'";
        cout << left << "=" << prefix << newNonTerminal << endl;
        cout << newNonTerminal << "=";

        // Print the remaining parts after prefix
        for (int i = 0; i < prods.size(); i++) {
            string suffix = prods[i].substr(prefix.size());
            if (suffix.empty()) suffix = "#"; // epsilon for empty string
            cout << suffix;
            if (i != prods.size() - 1) cout << "|";
        }
        cout << endl;
    }

    return 0;
}
