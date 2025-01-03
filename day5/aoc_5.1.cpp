#include <iostream>
#include <stdlib.h>
#include <vector>
#include <tuple>
#include <string>
#include <unordered_map>

using namespace std;
void getInputs();
int partOne();

unordered_map<int, vector<int>> adj_list;
vector<vector<int>> verification;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    getInputs();

    int partOneSum = partOne();
    cout << "Part One: " << partOneSum;
    
    return 0;
}

int partOne() {
    int sum = 0;
    // 75,97,47,61,53
    for (const auto& line : verification) {
        vector<int> queue;
        bool valid = true; 
        for (const int& num : line) {
            for (const int& shouldGoAfter : adj_list[num]) {
                for (int i = 0; i < queue.size(); i++) {
                    if (queue[i] == shouldGoAfter) {
                        valid = false;
                    }
                }
            }
            queue.push_back(num);
        }

        if (valid == true) {
            auto mid = queue.begin() + queue.size() / 2;
            sum += *mid;
        }    
    }
    return sum;
}

int partTwo() {
    int sum = 0;

    // 75,97,47,61,53
    for (const auto& line : verification) {
        vector<int> queue;
        bool valid = true; 
        for (const int& num : line) {
            for (const int& shouldGoAfter : adj_list[num]) {
                for (int i = 0; i < queue.size(); i++) {
                    if (queue[i] == shouldGoAfter) {
                        int tmp = queue[i];
                        queue[i] = shouldGoAfter;
                        queue.push_back(tmp);
                    }
                }
            }
            queue.push_back(num);
        }

        if (valid == true) {
            auto mid = queue.begin() + queue.size() / 2;
            sum += *mid;
        }
    }
    return sum;
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