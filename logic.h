#ifndef _LOGIC__H
#define _LOGIC__H

#include <fstream>
#include <algorithm>
#include <ctime>

#include "defs.h"
#include "graphics.h"
#include "keyboard.h"

using namespace std;

struct WordEntry {
    string word;
    string category;
};

struct Hangman {
    vector<WordEntry> wordList;
    WordEntry currentEntry;
    string secretWord;
    string guessedWord;
    string wrongGuesses;
    int badGuessCount;
    int score = 0;
    int level = 1;

    void init() {
        srand(time(0));
        wordList = loadWords("assets/word_list.txt");
        currentEntry = chooseWord(wordList);
        secretWord = getUpperCaseString(currentEntry.word);
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
            badGuessCount++;
        }
    }

    WordEntry chooseWord(const vector<WordEntry>& wordList) {
        if(wordList.size() > 0) {
            int randomIndex = rand() % wordList.size();
            return wordList[randomIndex];
        }
        else return {"", ""};
    }

    vector<WordEntry> loadWords(const string& filename) {
        vector<WordEntry> words;
        ifstream file(filename);
        if (!file) {
            cerr << "Can't open file " << filename << "!\n";
            exit(1);
        }
        string word, category;
        while (file >> word >> category) {
            words.push_back({word, category});
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
        return (won() || lost());
    }

    bool won() const {
        return (guessedWord == secretWord && badGuessCount < MAX_BAD_GUESSES);
    }

    bool lost() const {
        return (badGuessCount >= MAX_BAD_GUESSES);
    }

    void showHint(Keyboard& keyboard) {
        if (score < 10) return;

        vector<char> missing;
        for (int i = 0; i < secretWord.length(); ++i) {
            if (guessedWord[i] == '_') {
                missing.push_back(secretWord[i]);
            }
        }

        if (missing.empty()) return;

        char chosen = missing[rand() % missing.size()];

        for (auto& btn : keyboard.keys) {
            if (btn.letter == chosen && !btn.clicked) {
                btn.clicked = true;
                nextImage(btn);
                score -= 10;
                break;
            }
        }
    }

};

#endif
