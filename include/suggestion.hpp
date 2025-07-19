#ifndef SUGGESTION_HPP
#define SUGGESTION_HPP
#include <string>
#include <vector>

std::vector<std::string> loadAllSuggestions();
std::vector<std::string> fuzzySearch(const std::string& input, const std::vector<std::string>& suggestions);

#endif