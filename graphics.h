#pragma once

#include <string>
#include <vector>

const int MAX_BAD_GUESSES = 7;

void render(std::string& guessedWord, int& badGuessCount, const std::vector<std::string>& frames, const std::string& wrongGuesses);
void displayFinalResult(bool won, const std::string& secretWord);
std::vector<std::string> getImage(const std::string& filename);
void clearScreen();
