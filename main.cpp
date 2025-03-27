#include <iostream>
#include <ctime>
#include "game.h"
#include "graphics.h"
#include "wordlist.h"

using namespace std;

int main()
{
    srand(time(0));

    vector<string> frames = loadFrames("assets/hangman_frames.txt");
    vector<string> wordList = loadWords("assets/word_list.txt");

    string secretWord = chooseWord(wordList);
    int badGuessCount = 0;
    string guessedWord = string(secretWord.length(), '-');
    string wrongGuesses = "";

    do {
        render(guessedWord, badGuessCount, frames, wrongGuesses);
        char guess = readAGuess();
        cout << endl;
        if (contains(guess, secretWord)) {
            update(secretWord, guess, guessedWord);
        } else {
            badGuessCount++;
            wrongGuesses += guess;
            wrongGuesses += " ";
        }
    } while (badGuessCount < MAX_BAD_GUESSES && guessedWord != secretWord);

    render(guessedWord, badGuessCount, frames, wrongGuesses);
    if (guessedWord == secretWord)
        cout << "\nYOU WIN!!!\n";
    else
        cout << "\nYou lose. The answer is \"" << secretWord << "\".\n";

    return 0;
}
