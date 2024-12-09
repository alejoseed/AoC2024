#include <bits/stdc++.h>

using namespace std;
void getReportsAsArray(vector<vector<int>>& reports);

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int safeReports = 0;

  vector<vector<int>> reports;

  // Pass by ref to prepare reports vector
  getReportsAsArray(reports);

  for (auto const &line : reports) {
    int isLineSafe = 1;
    bool isFirstPass = true;
    bool isIncreasing = false;

    for (int i = 0; i < line.size() - 1; i++) {
      if (isFirstPass) {
        if (line.at(i) < line.at(i + 1)) {
          isIncreasing = true;
        };
        isFirstPass = false;
      }

      if ((abs(line.at(i) - line.at(i + 1)) == 0) || (abs(line.at(i) - line.at(i + 1)) > 3) 
          || (line.at(i) > line.at(i + 1) && isIncreasing) || 
             (line.at(i) < line.at(i + 1) && !isIncreasing)) {
        isLineSafe = 0;
        break;
      }
    }
    
    safeReports += isLineSafe;
  }
  cout << safeReports << "\n";

  return 0;
}

void getReportsAsArray(vector<vector<int>>& reports) {
  string line;

  while (getline(cin, line)) {
    stringstream tmpNums(line);
    vector<int> tmpArr;
    int num;

    while (tmpNums >> num) {
      tmpArr.push_back(num);
    }

    reports.push_back(tmpArr);
  };
}
