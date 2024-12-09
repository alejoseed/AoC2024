#include <bits/stdc++.h>

using namespace std;
void getReportsAsArray(vector<vector<int>> &reports);

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int safeReports = 0;

    vector<vector<int>> reports;

    // Pass by ref to prepare reports vector
    getReportsAsArray(reports);
    for (auto const &line : reports) {
        int isLineSafe = 1;
        
        int left = 0;
        int right = left + 1;
        int errors = 0;
        bool isAscending = line.at(left) > line.at(right);
        
        while (right < line.size()) {
            bool skip = false;
            int result = abs(line.at(left) - line.at(right));

            // Check that we are following either the same ascending or descending
            int curAscending = line.at(left) > line.at(right);

            if (errors >= 2) {
                isLineSafe = 0;
                break;
            }
            else if ((isAscending != curAscending)) {
                errors += 1;
                right += 1;
                skip = true;
            }
            else if ((result > 3 || isAscending != curAscending)) {
                // Means that the number was too big, advance one
                errors += 1;
                right += 1;
                skip = true;
            }
            else if (result == 0) {
                // We got to the same results as the other one but not life remaining
                isLineSafe = 0;
                break;
            }

            else {
                if (skip) {
                    left += right;
                    right += 1;
                }
                else {
                    left += 1;
                    right += 1;
                }
            }
        };

        safeReports += isLineSafe;
    }
    cout << safeReports << "\n";

    return 0;
}

void getReportsAsArray(vector<vector<int>> &reports)
{
    string line;

    while (getline(cin, line))
    {
        stringstream tmpNums(line);
        vector<int> tmpArr;
        int num;

        while (tmpNums >> num)
        {
            tmpArr.push_back(num);
        }

        reports.push_back(tmpArr);
    };
}