#include "../include/input.hpp"
#include "../include/execute.hpp"
#include "../include/history.hpp"
#include "../include/utils.hpp"
#include "../include/signal.hpp"
#include "../include/banner.hpp"
#include <iostream>

using namespace std;

int main() {
    showBanner();
    showWelcomeInfo();

    loadHistory(".lash_history");      // Load previous commands

    setupShellSignals();               // Handle Ctrl+C etc.

    while (true) {
        cout << "\033[1;35mLash>\033[0m " << flush;
        string line = getInputLine();   // Get raw input with history & prompt
        string trimmed = trim(line);    // Remove leading/trailing spaces

        if (trimmed.empty()) continue;
        if (trimmed == "exit") break;

        addToHistory(trimmed);               // Save to memory + file

        vector<string> args = parseInput(trimmed);  // Tokenize command

        executeCommand(args);                // Run command
    }

    return 0;
}