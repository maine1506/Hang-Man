#include <iostream>
#include <cstdlib> //dung rand()
#include <fstream>
#include <algorithm> //dung transform
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

string getLowerCaseString(const string& s) {
    string res = s;
    transform(s.begin(), s.end(), res.begin(), ::tolower);
    return res;
}

string chooseWord(const vector<string>& wordList) {
    if(wordList.size() > 0) {
        int randomIndex = rand() % wordList.size();
        return getLowerCaseString(wordList[randomIndex]);
    }
    else return "";
}
