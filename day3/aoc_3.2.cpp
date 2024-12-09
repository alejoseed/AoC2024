#include <bits/stdc++.h>
using namespace std;

class Parser {
 private:
  enum class ParserState {
    INITIAL,
    IN_FUNCTION,
    DO_PAREN,
    DONT_PAREN,
    MULT_PAREN,
    IN_NUMBER,
    IN_SEPARATOR,
    CLOSE_PAREN,
    ERROR
  };

  ParserState currentState;
  string functionName;
  string curNumber;
  array<int, 2> mult;
  long long totalSum;
  char character;

  void clearEverything() {
    functionName.clear();
    curNumber.clear();
    mult = {0, 0};
  }

  bool expression() {
    switch (currentState) {
      case ParserState::INITIAL:
        clearEverything();
        if (character == 'm' || character == 'd') {
          functionName += character;
          currentState = ParserState::IN_FUNCTION;
          return true;
        }
        break;

      case ParserState::IN_FUNCTION:
        if ((functionName == "m" && character == 'u') ||
            (functionName == "mu" && character == 'l')) {
          functionName += character;
          if (functionName == "mul") {
            currentState = ParserState::MULT_PAREN;
          }
          return true;
        }
        if ((functionName == "d" && character == 'o')) {
          functionName += character;
          return true;
        } else if ((functionName == "do" && character == '(')) {
          currentState = ParserState::DO_PAREN;
          return true;
        } else if ((functionName == "do" && character == 'n') ||
                   (functionName == "don" && character == '\'') ||
                   (functionName == "don'" && character == 't')) {
          functionName += character;
          if (functionName == "don't") {
            clearEverything();
            currentState = ParserState::DONT_PAREN;
          }
          return true;
        }
        currentState = ParserState::INITIAL;
        break;
      case ParserState::DO_PAREN:
        if (character == ')') {
          clearEverything();
          currentState = ParserState::INITIAL;
          return true;
        }
        currentState = ParserState::DONT_PAREN;
        clearEverything();
        break;
      case ParserState::DONT_PAREN:
        if (character == 'd') {
          functionName += character;
          return true;
        } else if (functionName == "d" && character == 'o') {
          functionName += character;
          return true;
        } else if (functionName == "do" && character == '(') {
          clearEverything();
          currentState = ParserState::DO_PAREN;
          return true;
        }
        clearEverything();
        break;
      case ParserState::MULT_PAREN:
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
        } else if (character == ',' && curNumber.size() <= 3) {
          mult[0] = stoi(curNumber);
          curNumber.clear();
          currentState = ParserState::IN_SEPARATOR;
          return true;
        } else if (character == ')' && curNumber.size() <= 3) {
          mult[1] = stoi(curNumber);
          if (mult[0] == 811 && mult[1] == 344) {
            cout << "811,344" << "\n";
          }
          cout << "A: " << mult[0] << " ," << " " << mult[1] << "\n";
          totalSum += mult[0] * mult[1];
          curNumber.clear();
          functionName.clear();
          currentState = ParserState::CLOSE_PAREN;
          return true;
        } else {
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
        if (character == 'd') {
          functionName += character;
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
  freopen("test.txt", "r", stdin);
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
