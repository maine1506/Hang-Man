#include <iostream>
#include <fstream>
#include "graphics.h"
#include <chrono>
#include <thread>

using namespace std;

void render(string& guessedWord, int& badGuessCount, const vector<string>& frames, const string& wrongGuesses) {
    clearScreen();

    cout << frames[badGuessCount] << endl;
    cout << "Word: " << guessedWord << endl;
    cout << "Wrong guesses: " << wrongGuesses << endl;
    cout << "Mistakes: " << badGuessCount << "/" << MAX_BAD_GUESSES << endl;
}


void displayFinalResult(bool won, const string& secretWord) {
    vector<string> DancingMan = getImage("assets/DancingMan.txt");
    vector<string> HangMan = getImage("assets/HangMan.txt");
    int i = 0;
    while (true) {
        clearScreen();

        cout << (won ? DancingMan[(i++) % DancingMan.size()] : HangMan[(i++) % HangMan.size()]);
        cout << endl;
        if (won)
            cout << "\nYOU WIN!!! The answer is \"" << secretWord << "\".\n";
        else
            cout << "\nYou lose. The answer is \"" << secretWord << "\".\n";
        this_thread::sleep_for(chrono::milliseconds(250));
    }
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

void clearScreen() {
    system("ClS");
    for (int i = 0; i < 16; i++) cout << "\n";
}

