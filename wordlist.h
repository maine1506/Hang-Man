#ifndef WORDLIST_H
#define WORDLIST_H

#include <string>
#include <vector>

std::vector<std::string> loadWords(const std::string& filename);
std::string chooseWord(const std::vector<std::string>& wordList);

#endif // WORDLIST_H
