#include <iostream>
#include <stdlib.h>
#include <vector>
#include <tuple>
#include <string>
#include <bits/stdc++.h>

using namespace std;
void createAdjList();

unordered_map<int, vector<int>> adj_list;
vector<vector<int>> verification;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string line;
    
    bool firstPart = true;
    while (getline(cin, line)) {
        string num;
        vector<int> curLine;

        for (const char &ch : line) {
            num += ch;
            if (ch == '|' && firstPart) {
                if (adj_list.contains(stoi(num))) {
                    continue;
                }
                adj_list.insert_or_assign(stoi(num), vector<int>{});
                num.clear();
            }
            else if (ch == ',' && firstPart == false) {
                curLine.push_back(stoi(num));
                num.clear();
            }
            else if (ch == '\n') {
                firstPart = false;
            }
        }

        if (firstPart == false) {
            verification.push_back(curLine);
        }
    }
    
    for (const auto &[key, line] : adj_list) {
        cout << "Key:" << " " << key;
    }

    return 0;

}

void createAdjList() {
    return;
}