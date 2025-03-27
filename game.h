#pragma once

#include <string>

void update(const std::string& secretWord, char guess, std::string &guessedWord);
bool contains(char guess, const std::string& secretWord);
char readAGuess();

