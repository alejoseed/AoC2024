#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

vector<vector<char>> grid;
tuple<int, int> getCoordinates();
bool outOfBounds(int row, int col);
bool isObstacle(tuple<int, int> inFrontOfCharacter);
void traverse(tuple<int, int> character);

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    OUT
};

struct hash_tuple {

    template <class T1, class T2>

    size_t operator()(
        const tuple<T1, T2>& x)
        const
    {
        return get<0>(x)
            ^ get<1>(x);
    }
};

unordered_set<tuple<int, int>, hash_tuple> visited;

Direction characterDirection;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string line;

    while (getline(cin, line)) {
        vector<char> curLine;
        curLine.reserve(line.size());
        for (const char& ch : line) {
            curLine.push_back(ch);
        }
        grid.push_back(curLine);
    }

    tuple<int, int> character = getCoordinates();

    traverse(character);

    cout << visited.size();
    return 0;
}

void traverse(tuple<int, int> character) {
    while (true) {
        int row = get<0>(character);
        int col = get<1>(character);

        if (outOfBounds(row, col) || characterDirection == OUT) {
            return;
        }

        if (!visited.contains(character)) visited.insert(character);

        switch (characterDirection)
        {
        case UP:
            if (isObstacle({ row - 1, col })) {
                int nc = col + 1;
                characterDirection = RIGHT;
                character = { row, nc };
            }
            else if (outOfBounds(row - 1, col)) {
                characterDirection = OUT;
                return;
            }
            else {
                int nr = row - 1;
                character = { nr, col };
            }
            break;
        case RIGHT:
            if (isObstacle({ row, col + 1 })) {
                int nr = row + 1;
                characterDirection = DOWN;
                character = { nr, col };
            }
            else if (outOfBounds(row, col + 1)) {
                characterDirection = OUT;
                return;
            }
            else {
                int nc = col + 1;
                character = { row, nc };
            }
            break;
        case DOWN:
            if (isObstacle({ row + 1, col })) {
                int nc = col - 1;
                characterDirection = LEFT;
                character = { row, nc };
            }
            else if (outOfBounds(row + 1, col)) {
                characterDirection = OUT;
                return;
            }
            else {
                int nr = row + 1;
                character = { nr, col };
            }
            break;
        case LEFT:
            if (isObstacle({ row, col - 1 })) {
                int nr = row - 1;
                characterDirection = UP;
                character = { nr , col };
            }
            else if (outOfBounds(row, col - 1)) {
                characterDirection = OUT;
                return;
            }
            else {
                int nc = col - 1;
                character = { row, nc };
            }
            break;
        default:
            return;
        }
    } 
}

bool outOfBounds(int row, int col) {
    return (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size());
}

bool isObstacle(tuple<int, int> inFrontOfCharacter) {
    int row = get<0>(inFrontOfCharacter);
    int col = get<1>(inFrontOfCharacter);
    if (!outOfBounds(row, col)) {
        return (grid[row][col] == '#');
    }
    return false;
}

tuple<int, int> getCoordinates() {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '^') {
                characterDirection = UP;
                return { i, j };
            }
            if (grid[i][j] == 'v') {
                characterDirection = DOWN;
                return { i, j };
            }
            if (grid[i][j] == '>') {
                characterDirection = RIGHT;
                return { i, j };
            }
            if (grid[i][j] == '<') {
                characterDirection = LEFT;
                return { i, j };
            }
        }
    }
    return { -1, -1 };
}