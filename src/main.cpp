// Includes all needed header files and libraries
#include "../include/input.hpp"
#include "../include/execute.hpp"
#include "../include/history.hpp"
#include "../include/signal.hpp"
#include "../include/banner.hpp"
#include "../include/suggestion.hpp"
#include "../include/configuration.hpp"
#include "../include/alias.hpp"
#include <iostream>
#include <unistd.h>
#include <limits.h>

using namespace std;

int main() {
    // Shows banner and welcomeInfo. Go to banner.cpp
    showBanner(); 
    showWelcomeInfo();

    runCFile(".lashrc");  // Supports user configuration. Go to configuration.cpp

    loadHistory(".lash_history"); // Load previous commands. Go to history.cpp

    setupShellSignals(); // Handle Ctrl+C etc. Go to signal.cpp

    while (true) {
        // Print prompt
        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));

        cout << "\033[1;35mLash \033[0m ";
        cout << "\033[1;36m" << cwd << "\033[0m";
        cout << " > " << flush;
        
        vector<string> commands = loadAllSuggestions(); // Load suggestions from all methods. Go to suggestion.cpp
        string line = getInputWithSuggestions(commands); // Get raw input with suggestions. Go to input.cpp
        string trimmed = trim(line); // Remove leading or trailing spaces. Go to input.cpp

        if (trimmed.empty()) continue;
        if (trimmed == "exit") break;

        addToHistory(trimmed); // Save to memory + file. Go to history.cpp

        vector<string> args = parseInput(trimmed); // Tokenize command. Go to input.cpp

        args = resolveAlias(args); // Resolve alias, if any. Go to alias.cpp

        executeCommand(args); // Run command. Go to execute.cpp
    }

    return 0;
}