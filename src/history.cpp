#include "../include/history.hpp"
#include <vector>
#include <string>
#include <fstream>

static std::vector<std::string> history;
static int historyIndex = 0;

void loadHistory(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) history.push_back(line);
    }
    historyIndex = history.size();  // set to end
}

void addToHistory(const std::string& cmd) {
    if (!cmd.empty()) {
        history.push_back(cmd);
        std::ofstream file(".lash_history", std::ios::app);
        if (file) file << cmd << "\n";
        historyIndex = history.size();
    }
}

std::string getPrevCommand() {
    if (historyIndex > 0) {
        historyIndex--;
        return history[historyIndex];
    }
    return "";
}

std::string getNextCommand() {
    if (historyIndex < (int)history.size() - 1) {
        historyIndex++;
        return history[historyIndex];
    } else {
        historyIndex = history.size();
        return "";
    }
}