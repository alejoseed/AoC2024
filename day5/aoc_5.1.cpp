#include <iostream>
#include <stdlib.h>
#include <vector>
#include <tuple>
#include <string>
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
void getInputs();

unordered_map<int, vector<int>> adj_list;
vector<vector<int>> verification;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    getInputs();

    for (const auto& line : verification) {
        bool exists = false;
        for (int i = 0; i < line.size() - 1; i++) {
            bool curNumExists = false;
            int key = line[i];
            for (const auto& val : adj_list[key]) {
                for (int j = i + 1; j < line.size(); j++) {
                    if (line[j] == val) curNumExists = true;
                }
                if (curNumExists == false) { 
                    exists = false;
                    break;
                }
                else { 
                    exists = true;
                    break;
                };
            }
        }
        if (exists == true) cout << "true line" << "\n";
    }
    return 0;
}

void getInputs() {
    string line;
    bool firstPart = true;

    while (getline(cin, line)) {
        if (line.size() == 0) {
            firstPart = false;
            continue;
        };

        if (firstPart) {
            int key, val;
            key = stoi(line.substr(0, 2));
            val = stoi(line.substr(3, line.size() - 1));

            if (adj_list.contains(key)) {
                adj_list[key].push_back(val);
                if (!adj_list.contains(val)) {
                    vector<int> temp;
                    adj_list.insert_or_assign(val, temp);
                }
            }
            else {
                vector<int> curLine;
                curLine.push_back(val);
                adj_list.insert_or_assign(key, curLine);
            }
        }
        else {
            string num;
            vector<int> curLine;
            for (const char& ch : line) {
                if (ch == ',' && num.size() == 2) {
                    curLine.push_back(stoi(num));
                    num.clear();
                    continue;
                }
                num += ch;
            }
            if (num.size() == 2) {
                curLine.push_back(stoi(num));
            }
            verification.push_back(curLine);
        }
    }
}