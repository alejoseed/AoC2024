#include <iostream>
#include <stdlib.h>
#include <vector>
#include <tuple>
#include <string>

using namespace std;
bool dfs(vector<vector<char>> grid, int r, int c, tuple<int,int> dir, int step);

vector<tuple<int, int>> directions = {
    {0, 1},    // right
    {0, -1},   // left
    {1, 0},    // down
    {-1, 0},   // up
    {1, 1},    // down-right
    {-1, -1},  // up-left
    {1, -1},   // down-left
    {-1, 1}    // up-right
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
            for (const auto& dir : directions) {
                if (grid[i][j] == 'A') {
                    if (dfs(grid, i, j, dir, 0)) {
                        counter += 1;
                    };
                }
            }
        }
    }

    cout << counter << "\n";
    return 0;
}

bool dfs(vector<vector<char>> grid, int r, int c, tuple<int,int> dir, int step) {
    
    if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size())
        return false;
    
    if (step == 0 && grid[r][c] != 'X') return false;
    if (step == 1 && grid[r][c] != 'M') return false;
    if (step == 2 && grid[r][c] != 'A') return false;
    if (step == 3 && grid[r][c] != 'S') return false;
    
    if (step == 3) return true;

    int nr = r + get<0>(dir);
    int nc = c + get<1>(dir);

    return dfs(grid, nr, nc, dir, step + 1);
}