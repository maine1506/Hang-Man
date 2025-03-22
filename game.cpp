#include <iostream>
#include <cctype>
#include "game.h"

using namespace std;

bool contains(char guess, const string& secretWord) {
    return (secretWord.find(guess) != string::npos);
}

void update(const string& secretWord, char guess, string &guessedWord) {
    for (size_t i = 0; i < secretWord.length(); i++) {
        if (secretWord[i] == guess) {
            guessedWord[i] = guess;
        }
    }
}

char readAGuess() {
    char guess;
    cout << "Your guess: ";
    cin >> guess;
    return tolower(guess);
}
