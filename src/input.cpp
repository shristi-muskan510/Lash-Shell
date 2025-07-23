#include "../include/input.hpp"
#include "../include/history.hpp"
#include "../include/suggestion.hpp"
#include <termios.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

static struct termios originalTermios;

void showPrompt(string input){
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    cout << "\33[2K\r";
    cout << "\033[1;35mLash>\033[0m ";
    cout << "\033[1;36m" << cwd << "\033[0m";
    cout << " > " << input << flush;

}

vector<string> parseInput(const string& input) {
    istringstream iss(input);
    vector<std::string> tokens;
    string token;
    while (iss >> token)
        tokens.push_back(token);
    return tokens;
}

string trim(const string& input) {
    size_t start = input.find_first_not_of(" \t\n\r");
    size_t end   = input.find_last_not_of(" \t\n\r");

    if (start == string::npos) return "";

    return input.substr(start, end - start + 1);
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalTermios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &originalTermios);
    atexit(disableRawMode);
    struct termios raw = originalTermios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

std::string getInputWithSuggestions(const std::vector<std::string>& commandList) {
    enableRawMode();

    std::string input;
    char c;

    int suggestionIndex = 0;
    vector<string> suggestions;

    while (read(STDIN_FILENO, &c, 1) == 1) {
        if (c == '\n') {
            if (!suggestions.empty()) {
                input = suggestions[suggestionIndex];
                suggestions.clear();  // Hide suggestions
                suggestionIndex = 0;

                // Redraw the prompt with updated input
                showPrompt(input);
            } else {
                cout << endl;
                break; // Actually execute the command
            }
        } else if (c == 127 || c == 8) {  // backspace
            if (!input.empty()) {
                input.pop_back();
                cout << "\b \b" << flush;
            }
        } else if (c == 27) {
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) != 1) break;
            if (read(STDIN_FILENO, &seq[1], 1) != 1) break;

            if (seq[0] == '[') {
                if (seq[1] == 'A') {  // ↑
                    input = getPrevCommand();
                    showPrompt(input);
                } else if (seq[1] == 'B') {  // ↓
                    input = getNextCommand();
                    showPrompt(input);
                } else if (seq[1] == 'D'){
                    if (suggestionIndex > 0) suggestionIndex--;
                } else if (seq[1] == 'C'){
                    if (suggestionIndex < suggestions.size() - 1) suggestionIndex++;
                }
            }
        } else {
            input += c;
            cout << c << flush;  // Show typed char
        }

        suggestions = fuzzySearch(input, commandList);
        showPrompt(input);

        if (!suggestions.empty()) {
            cout << "\n";
            cout << "\33[2K\r";

            for (int i = 0; i < 3; ++i) {
                if (i == suggestionIndex)
                    cout << "\033[7m";  // Reverse for highlight
                cout << suggestions[i] << "\033[0m ";
            }

            cout << "\033[1A";
            cout << "\33[2K\r"; 
        }
        
        showPrompt(input);

    }

    disableRawMode();

    for (size_t i = 0; i < suggestions.size(); ++i) {
        cout << "\033[A"; 
        cout << "\33[2K\r";
    }

    std::cout << "\33[2K\r"; 
    std::cout.flush();

    return !suggestions.empty() ? suggestions[suggestionIndex] : input;
}