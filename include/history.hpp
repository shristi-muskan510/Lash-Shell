#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <string>

void loadHistory(const std::string& filename);
void addToHistory(const std::string& cmd);
std::string getPrevCommand();
std::string getNextCommand();

#endif