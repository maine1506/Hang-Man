#include <iostream>
#include <fstream>
#include "graphics.h"

using namespace std;

void render(string& guessedWord, int& badGuessCount, const vector<string>& frames, const string& wrongGuesses) {
    system("CLS");
    for (int i = 0; i < 15; i++) cout << endl;

    cout << frames[badGuessCount] << endl;
    cout << "Word: " << guessedWord << endl;
    cout << "Wrong guesses: " << wrongGuesses << endl;
    cout << "Mistakes: " << badGuessCount << "/" << MAX_BAD_GUESSES << endl;
}

vector<string> loadFrames(const string& filename) {
    vector<string> frames;
    ifstream file(filename);
    if (!file) {
        cerr << "Không thể mở file " << filename << "!\n";
        exit(1);
    }
    string line, frame;
    while (getline(file, line)) {
        if (line.empty()) {
            frames.push_back(frame);
            frame.clear();
        } else {
            frame += line + "\n";
        }
    }
    if (!frame.empty()) frames.push_back(frame);
    file.close();
    return frames;
}
