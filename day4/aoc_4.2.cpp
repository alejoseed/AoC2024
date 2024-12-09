#include <stdlib.h>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;
bool dfs(vector<vector<char>> grid, int r, int c, tuple<int, int> dir,
         int step);
bool checkDiagonals(vector<vector<char>> grid, int r, int c);

vector<tuple<int, int>> directions = {
    {-1, 1},   // up-right
    {1, -1},   // down-left
    {-1, -1},  // up-left
    {1, 1},    // down-right
};

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  vector<vector<char>> grid;

  char ch;
  vector<char> line;

  // Read entire input first
  while (cin.get(ch)) {
    if (ch == '\n') {
      grid.push_back(line);
      line.clear();
      continue;
    }

    line.push_back(ch);
  }

  grid.push_back(line);

  int counter = 0;

  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == 'A') {
        if (checkDiagonals(grid, i, j)) {
          counter += 1;
        };
      }
    }
  }

  cout << counter << "\n";
  return 0;
}

bool checkDiagonals(vector<vector<char>> grid, int r, int c) {
  vector<tuple<int, int>> newDirections;

  for (const auto &dir : directions) {
    int nr = r + get<0>(dir);
    int nc = c + get<1>(dir);
    if (nr < 0 || nr >= grid.size() || nc < 0 || nc >= grid[0].size()) {
      return false;
    }
    newDirections.push_back({nr, nc});
  }

  if (((grid[get<0>(newDirections[0])][get<1>(newDirections[0])] == 'M' &&
        grid[get<0>(newDirections[1])][get<1>(newDirections[1])] == 'S') ||
       (grid[get<0>(newDirections[0])][get<1>(newDirections[0])] == 'S' &&
        grid[get<0>(newDirections[1])][get<1>(newDirections[1])] == 'M')) &&
      ((grid[get<0>(newDirections[2])][get<1>(newDirections[2])] == 'M' &&
        grid[get<0>(newDirections[3])][get<1>(newDirections[3])] == 'S') ||
       (grid[get<0>(newDirections[2])][get<1>(newDirections[2])] == 'S' &&
        grid[get<0>(newDirections[3])][get<1>(newDirections[3])] == 'M')))
    return true;

  return false;
}

bool dfs(vector<vector<char>> grid, int r, int c, tuple<int, int> dir,
         int step) {
  if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size()) return false;

  if (step == 0 && grid[r][c] != 'X') return false;
  if (step == 1 && grid[r][c] != 'M') return false;
  if (step == 2 && grid[r][c] != 'A') return false;
  if (step == 3 && grid[r][c] != 'S') return false;

  if (step == 3) return true;

  int nr = r + get<0>(dir);
  int nc = c + get<1>(dir);

  return dfs(grid, nr, nc, dir, step + 1);
}