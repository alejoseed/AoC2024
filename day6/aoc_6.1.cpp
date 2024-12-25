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
int loopFinder(tuple<int, int> character);
bool isObstacle(tuple<int, int> inFrontOfCharacter);
bool isObstacleOrCircleBool(tuple<int, int> inFrontOfCharacter);

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
    tuple<int, int> initialCoordinate = character;

    originalDirection = characterDirection;

    char initialChar = grid[get<0>(character)][get<1>(character)];

    traverse(character);

    //// Make the initial position the arrow again.
    grid[get<0>(character)][get<1>(character)] = initialChar;
    int totalLoops = 0;
    
    for (const auto& visit : visited) {
        if (visit._Equals(initialCoordinate)) 
            continue;

        char originalChar = grid[get<0>(visit)][get<1>(visit)];
        grid[get<0>(visit)][get<1>(visit)] = 'O';
        totalLoops += loopFinder(character);
        grid[get<0>(visit)][get<1>(visit)] = originalChar;
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


int loopFinder(tuple<int, int> character) {
    unordered_map<tuple<int, int>, int, hash_tuple> possibles;
    Direction tmpDir = originalDirection;
    int row = get<0>(character);
    int col = get<1>(character);
    while (true) {


        if (outOfBounds(row, col) || tmpDir == OUT) {
            return 0;
        }

        if (possibles.find(character) != possibles.end()) {
            if (possibles[character] > 4) 
                return 1;
        }

        possibles[character]++;

        switch (tmpDir)
        {
        case UP:
            if (isObstacleOrCircleBool({ row - 1, col })) {
                int nc = col + 1;
                tmpDir = RIGHT;
                character = { row, nc };
            }
            else {
                int nr = row - 1;
                character = { nr, col };
            }
            break;
        case RIGHT:
            if (isObstacleOrCircleBool({ row, col + 1 })) {
                int nr = row + 1;
                tmpDir = DOWN;
                character = { nr, col };
            }
            else {
                int nc = col + 1;
                character = { row, nc };
            }
            break;
        case DOWN:
            if (isObstacleOrCircleBool({ row + 1, col })) {
                int nc = col - 1;
                tmpDir = LEFT;
                character = { row, nc };
            }
            else {
                int nr = row + 1;
                character = { nr, col };
            }
            break;
        case LEFT:
            if (isObstacleOrCircleBool({ row, col - 1 })) {
                int nr = row - 1;
                tmpDir = UP;
                character = { nr , col };
            }
            else {
                int nc = col - 1;
                character = { row, nc };
            }
            break;
        default:
            return 0;
        }
    }
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


bool isObstacleOrCircleBool(tuple<int, int> inFrontOfCharacter) {
    int row = get<0>(inFrontOfCharacter);
    int col = get<1>(inFrontOfCharacter);
    if (!outOfBounds(row, col)) {
        if (grid[row][col] == '#') return true;
        if (grid[row][col] == 'O') return true;
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