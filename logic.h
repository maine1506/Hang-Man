#ifndef _HANGMAN__H
#define _HANGMAN__H

#include <fstream>
#include <algorithm>

#include "defs.h"
#include "graphics.h"

using namespace std;

struct Hangman {
    vector<string> wordList = loadWords("assets/word_list.txt");
    vector<string> frames = getImage("assets/hangman_frames.txt");
    char guess;
    string secretWord = chooseWord(wordList);
    string nextFrame;
    string guessedWord = string(secretWord.size(), '-');
    string wrongGuesses = "";
    int badGuessCount = 0;


    void init() {
        srand(time(0));
        badGuessCount = 0;
        secretWord = chooseWord(wordList);
        guessedWord = string(secretWord.size(), '-');
        wrongGuesses = "";
        nextFrame = frames[badGuessCount];
    }

    void nextImage(char guess) {
        if (contains(guess, secretWord)) {
            update(secretWord, guess, guessedWord);
        } else {
            badGuessCount++;
            wrongGuesses = wrongGuesses + guess + " ";
            nextFrame = frames[badGuessCount];
        }
    }

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
        cin >> guess;
        return tolower(guess);
    }

    string chooseWord(const vector<string>& wordList) {
        if(wordList.size() > 0) {
            int randomIndex = rand() % wordList.size();
            return getLowerCaseString(wordList[randomIndex]);
        }
        else return "";
    }

    vector<string> loadWords(const string& filename) {
    vector<string> words;
    ifstream file(filename);
    if (!file) {
        cerr << "Can't open file " << filename << "!\n";
        exit(1);
    }
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();
    return words;
}

vector<string> getImage(const string& filename) {
    vector<string> Image;
    ifstream file(filename);
    if (!file) {
        cerr << "Không thể mở file " << filename << "!\n";
        exit(1);
    }
    string line, frame;
    while (getline(file, line)) {
        if (line.empty()) {
            Image.push_back(frame);
            frame.clear();
        } else {
            frame += line + "\n";
        }
    }
    if (!frame.empty()) Image.push_back(frame);
    file.close();
    return Image;
}

    string getLowerCaseString(const string& s) {
        string res = s;
        transform(s.begin(), s.end(), res.begin(), ::tolower);
        return res;
    }

    bool endGame() {
        return (guessedWord == secretWord || badGuessCount == MAX_BAD_GUESSES);
    }
};

#endif // _HANGMAN__H
