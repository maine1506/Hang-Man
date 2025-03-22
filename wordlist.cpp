#include <iostream>
#include <cstdlib>
#include <fstream>
#include "wordlist.h";

using namespace std;

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

string chooseWord(const vector<string>& wordList) {
    int randomIndex = rand() % wordList.size();
    return wordList[randomIndex];
}
