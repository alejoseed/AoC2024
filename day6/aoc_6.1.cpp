#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

vector<vector<char>> grid;
tuple<int, int> getCoordinates();
bool outOfBounds(int row, int col);
bool isObstacle(tuple<int, int> inFrontOfCharacter);
void traverse(tuple<int, int> character);
int loopCount(tuple<int, int> character);
int isObstacleOrCircle(tuple<int, int> inFrontOfCharacter);

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
unordered_map<tuple<int, int>, int> visitedMap;

Direction characterDirection;
Direction originalDirection;

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
    originalDirection = characterDirection;

    char initialChar = grid[get<0>(character)][get<1>(character)];

    traverse(character);

    // Make the initial position the arrow again.
    grid[get<0>(character)][get<1>(character)] = initialChar;
    
    int totalLoops = 0;
    for (int i = 0; (unsigned)i < grid.size(); i++) {
        
        for (int j = 0; (unsigned)j < grid[i].size(); j++) {
            if (i == get<0>(character) && j == get<1>(character)) continue;
            char originalChar = grid[i][j];
            if (originalChar == '#') continue;

            grid[i][j] = 'O';
            // Make the current character a O. If we hit that O twice we got a loop.
            totalLoops += loopCount(character);
            grid[i][j] = originalChar;
        }

    }
    
    cout << "Total loops: " << totalLoops << '\n';

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

        if (!visited.contains(character)) {
            visited.insert(character);
        }

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

int loopCount(tuple<int, int> character) {
    int visitedTwice = 0;
    Direction tmpDir = originalDirection;

    while (true) {
        int row = get<0>(character);
        int col = get<1>(character);

        if (outOfBounds(row, col) || tmpDir == OUT) {
            return 0;
        }
        
        if (visitedMap[{row, col}] >= 2) return 1;

        int isObstacleOrCir;
        switch (tmpDir)
        {
        case UP:
            if (outOfBounds(row - 1, col)) {
                tmpDir = OUT;
                return 0;
            }
            isObstacleOrCir = isObstacleOrCircle({ row - 1, col });
            if (isObstacleOrCir == 0 || isObstacleOrCir == 1) {

                if (isObstacleOrCir == 1) visitedMap[{row, col}]++;
                tmpDir = RIGHT;
                character = { row, col + 1 };
            }
            else {
                character = { row - 1, col };
            }
            break;

        case RIGHT:
            if (outOfBounds(row, col + 1)) {
                tmpDir = OUT;
                return 0;
            }
            isObstacleOrCir = isObstacleOrCircle({ row, col + 1 });
            if (isObstacleOrCir == 0 || isObstacleOrCir == 1) {
                if (isObstacleOrCir == 1) visitedMap[{row, col}]++;
                tmpDir = DOWN;
                character = { row + 1, col };
            }
            else {
                character = { row, col + 1 };
            }
            break;

        case DOWN:
            if (outOfBounds(row + 1, col)) {
                tmpDir = OUT;
                return 0;
            }
            isObstacleOrCir = isObstacleOrCircle({ row + 1, col });
            if (isObstacleOrCir == 0 || isObstacleOrCir == 1) {
                if (isObstacleOrCir == 1) visitedMap[{row, col}]++;
                tmpDir = LEFT;
                character = { row, col - 1 };
            }
            else {
                character = { row + 1, col };
            }
            break;

        case LEFT:
            if (outOfBounds(row, col - 1)) {
                tmpDir = OUT;
                return 0;
            }
            isObstacleOrCir = isObstacleOrCircle({ row, col - 1 });
            if (isObstacleOrCir == 0 || isObstacleOrCir == 1) {
                if (isObstacleOrCir == 1) visitedMap[{row, col}]++;
                tmpDir = UP;
                character = { row - 1, col };
            }
            else {
                character = { row, col - 1 };
            }
            break;
        }
    }
    return 0;
}

bool outOfBounds(int row, int col) {
    return ((unsigned)row < 0 || (unsigned)row >= grid.size() || (unsigned)col < 0 || (unsigned)col >= grid[0].size());
}

bool isObstacle(tuple<int, int> inFrontOfCharacter) {
    int row = get<0>(inFrontOfCharacter);
    int col = get<1>(inFrontOfCharacter);
    if (!outOfBounds(row, col)) {
        return (grid[row][col] == '#');
    }
    return false;
}


int isObstacleOrCircle(tuple<int, int> inFrontOfCharacter) {
    int row = get<0>(inFrontOfCharacter);
    int col = get<1>(inFrontOfCharacter);
    if (!outOfBounds(row, col)) {
        if (grid[row][col] == '#') return 0;
        if (grid[row][col] == 'O') return 1;
    }
    return 2;
}


tuple<int, int> getCoordinates() {
    for (int i = 0; (unsigned)i < grid.size(); i++) {
        for (int j = 0; (unsigned)j < grid[i].size(); j++) {
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