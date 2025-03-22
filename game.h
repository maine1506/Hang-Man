#ifndef GAME_H
#define GAME_H

#include <string>

void update(const std::string& secretWord, char guess, std::string &guessedWord);
bool contains(char guess, const std::string& secretWord);
char readAGuess();

#endif // GAME_H
