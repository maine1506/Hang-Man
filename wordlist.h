#pragma once

#include <string>
#include <vector>

std::vector<std::string> loadWords(const std::string& filename);
std::string chooseWord(const std::vector<std::string>& wordList);
std::string getLowerCaseString(const std::string& s);

