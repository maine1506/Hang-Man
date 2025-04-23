#ifndef _LOGIC__H
#define _LOGIC__H

#include <fstream>
#include <algorithm>
#include <ctime>

#include "defs.h"

using namespace std;

struct Hangman {
    vector<string> wordList;
    string secretWord;
    string guessedWord;
    string wrongGuesses;
    int badGuessCount;

    void init() {
        srand(time(0));
        wordList = loadWords("assets/word_list.txt");
        secretWord = chooseWord(wordList);
        guessedWord = string(secretWord.size(), '_');
        badGuessCount = 0;
        wrongGuesses.clear();
    }

    bool contains(char guess) {
        return (secretWord.find(guess) != string::npos);
    }

    void update(char guess) {
        for (size_t i = 0; i < secretWord.length(); i++) {
            if (secretWord[i] == guess) {
                guessedWord[i] = guess;
            }
        }
    }

    void nextImage(LetterButton& btn) {
        if (contains(btn.letter)) {
            btn.correct = true;
            update(btn.letter);
        } else {
            btn.correct = false;
            badGuessCount++;
        }
    }

    string chooseWord(const vector<string>& wordList) {
        if(wordList.size() > 0) {
            int randomIndex = rand() % wordList.size();
            return getUpperCaseString(wordList[randomIndex]);
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

    string getUpperCaseString(const string& s) {
        string res = s;
        transform(s.begin(), s.end(), res.begin(), ::toupper);
        return res;
    }

    bool gameOver() {
        return (guessedWord == secretWord || badGuessCount == MAX_BAD_GUESSES);
    }
};


#endif
