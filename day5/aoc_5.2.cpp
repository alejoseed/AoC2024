#include <iostream>
#include <stdlib.h>
#include <vector>
#include <tuple>
#include <string>
#include <unordered_map>

using namespace std;
void getInputs();
int partOne();
int partTwo();

unordered_map<int, vector<int>> adj_list;
vector<vector<int>> verification;
vector<vector<int>> invalidOnes;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    getInputs();

    int partOneSum = partOne();
    cout << "Part One: " << partOneSum << "\n";

    int partTwoSum = partTwo();
    cout << "Part Two: " << partTwoSum << "\n";

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
        else {
            invalidOnes.push_back(line);
        }
    }
    return sum;
}

// The only problem with this is that the vector ends up being reversed. That is something that I need to figure out.
// I implemented some sorting algorithm out of the top of my head on this one that looks like bubble sort
int partTwo() {
    int sum = 0;


    for (const auto& line : invalidOnes) {
        vector<int> queue(line);

        for (int i = 0; i < queue.size(); i++) {
            for (int j = 0; j < queue.size(); j++) {
                if (i == j) continue;
                // For the current num on j, check if any of the numbers in that current vector are equal to the number in [i], which goes before j
                for (const int& shouldGoAfter : adj_list[queue[j]]) {
                    if (shouldGoAfter == queue[i]) {
                        // This means that using the num in j, we found a number in the line that is not supposed to be before it. So let's swap i and j
                        int tmp = queue[i];
                        queue[i] = queue[j];
                        queue[j] = tmp;
                    };
                }
            }
        }

        auto mid = queue.begin() + queue.size() / 2;
        sum += *mid;

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