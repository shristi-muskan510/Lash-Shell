#ifndef HISTORY_HPP
#define HISTORY_HPP

#pragma once
#include <string>
#include <vector>

void loadHistory(const std::string& filename);
void addToHistory(const std::string& cmd);
std::string getInputWithHistory();

#endif