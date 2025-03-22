#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>

const int MAX_BAD_GUESSES = 7;

void render(std::string& guessedWord, int& badGuessCount, const std::vector<std::string>& frames, const std::string& wrongGuesses);
std::vector<std::string> loadFrames(const std::string& filename);

#endif // GRAPHICS_H
