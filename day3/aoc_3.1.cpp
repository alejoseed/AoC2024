#include <bits/stdc++.h>
using namespace std;

class Parser {
private:
    enum class ParserState {
        INITIAL,
        IN_FUNCTION,
        OPEN_PAREN,
        IN_NUMBER,
        IN_SEPARATOR,
        CLOSE_PAREN,
        ERROR
    };

    ParserState currentState;
    string functionName;
    string curNumber;
    string text;
    array<int, 2> mult;
    long long totalSum;
    char separatorChar;
    char character;

    void clearEverything() {
        functionName.clear();
        curNumber.clear();
        text.clear();
        mult = {0, 0};
        separatorChar = '\0';
    }

    bool expression() {
        switch (currentState) {
            case ParserState::INITIAL:
                clearEverything();
                if (character == 'm') {
                    functionName += 'm';
                    currentState = ParserState::IN_FUNCTION;
                    return true;
                }
                break;

            case ParserState::IN_FUNCTION:
                if ((functionName == "m" && character == 'u') ||
                    (functionName == "mu" && character == 'l')) {
                    functionName += character;
                    if (functionName == "mul") {
                        currentState = ParserState::OPEN_PAREN;
                    }
                    return true;
                }
                currentState = ParserState::INITIAL;
                break;

            case ParserState::OPEN_PAREN:
                if (character == '(') {
                    currentState = ParserState::IN_NUMBER;
                    return true;
                }
                currentState = ParserState::INITIAL;
                break;

            case ParserState::IN_NUMBER:
                if (isdigit(character) && curNumber.size() <= 3) {
                    curNumber.append(1, character);
                    return true;
                }
                else if (character == ',' && curNumber.size() <= 3) {
                    mult[0] = stoi(curNumber);
                    curNumber.clear();
                    currentState = ParserState::IN_SEPARATOR;
                    return true;
                }
                else if (character == ')' && curNumber.size() <= 3) {
                    mult[1] = stoi(curNumber);
                    totalSum += mult[0] * mult[1];
                    curNumber.clear();
                    functionName.clear();
                    currentState = ParserState::CLOSE_PAREN;
                    return true;
                }
                else {
                    currentState = ParserState::INITIAL;
                    return false;
                }
                break;

            case ParserState::IN_SEPARATOR:
                if (isdigit(character)) {
                    curNumber = character;
                    currentState = ParserState::IN_NUMBER;
                    return true;
                }
                currentState = ParserState::INITIAL;
                break;

            case ParserState::CLOSE_PAREN:
                if (character == 'm') {
                    functionName += 'm';
                    currentState = ParserState::IN_FUNCTION;
                    return true;
                }
                currentState = ParserState::INITIAL;
                break;

            case ParserState::ERROR:
                currentState = ParserState::INITIAL;
                return false;
        }
        return false;
    }

public:
    Parser() : currentState(ParserState::INITIAL), totalSum(0) {}

    long long parse(const string& input) {
        for (char ch : input) {
            character = ch;
            expression();
        }
        return totalSum;
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    string input;
    char ch;
    while (cin.get(ch)) {
        input += ch;
    }

    Parser parser;
    cout << parser.parse(input) << "\n";
    return 0;
}