#include <iostream>

using namespace std;

string update(string secretWord, char guess, string guessedWord);
bool contains(char guess, string secretWord);
void render(string guessedWord, int badGuessCount);
char readAGuess();
const int MAX_BAD_GUESSES = 7;


int main()
{
    string secretWord = "book";
    int badGuessCount = 0;
    string guessedWord = string(secretWord.length(), '-');

    do {
        render(guessedWord, badGuessCount);
        char guess = readAGuess();
        cout << endl;
        if (contains(guess, secretWord)) {
            guessedWord = update(secretWord, guess, guessedWord);
        }
        else badGuessCount++;
    } while (badGuessCount < MAX_BAD_GUESSES && guessedWord != secretWord);

    render(guessedWord, badGuessCount);
    if (guessedWord == secretWord) cout << "You win!";
    else cout << "You lose. The answer is \"" << secretWord << "\"." << endl;
    return 0;
}

string update(string secretWord, char guess, string guessedWord) {
    int size = secretWord.length();
    for (int i = 0; i < size; i++) {
        if (guess == secretWord[i]) {
            guessedWord[i] = guess;
        }
    }
    return guessedWord;
}

bool contains(char guess, string secretWord) {
    if (secretWord.find(guess) != string::npos) return 1;
    return 0;
}

char readAGuess() {
    char guess;
    cout << "Your guess: ";
    cin >> guess;
    return guess;
}

void render(string guessedWord, int badGuessCount) {
    cout << guessedWord << endl;
    cout << "Number of wrong guesses: " << badGuessCount << endl;
}
