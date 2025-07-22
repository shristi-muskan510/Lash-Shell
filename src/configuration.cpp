#include "../include/configuration.hpp"
#include "../include/input.hpp"
#include "../include/execute.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

void runCFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        string trimmed = trim(line);
        if (trimmed.empty() || trimmed[0] == '#') continue;

        vector<string> args = parseInput(trimmed);
        if (!args.empty())
            executeCommand(args);
    }
}