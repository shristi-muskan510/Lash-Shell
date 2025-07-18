#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>
#include <vector>

#pragma once
std::string getInputWithSuggestions();
void enableRawMode();
void disableRawMode();
std::vector<std::string> parseInput(const std::string& input);
std::string trim(const std::string& input);

#endif