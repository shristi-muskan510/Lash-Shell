#include "../include/history.hpp"
#include <fstream>
#include <ncurses.h>
#include "history.hpp"
using namespace std;

static vector<string> history;
static int historyIndex = -1;

void loadHistory(const string& filename){
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        history.push_back(line);
    }
}

void addToHistory(const string &cmd){
    if (cmd.empty()) return;
    
    history.push_back(cmd);

    ofstream file(".lash_history", ios::app); // append mode
    if (file.is_open())
        file << cmd << "\n";
}

string getInputWithHistory()
{
    string input;
    int ch;
    historyIndex = history.size();

    int promptY, promptX;
    getyx(stdscr, promptY, promptX);

    // Print prompt once
    move(promptY+1, 0);
    clrtoeol();
    printw("Lash> ");
    refresh();

    while ((ch = getch()) != '\n') {
        if (ch == KEY_UP) {
            if (historyIndex > 0) {
                historyIndex--;
                input = history[historyIndex];
            }
        } else if (ch == KEY_DOWN) {
            if (historyIndex < history.size() - 1) {
                historyIndex++;
                input = history[historyIndex];
            } else {
                historyIndex = history.size();
                input.clear();
            }
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            if (!input.empty()) input.pop_back();
        } else {
            input += static_cast<char>(ch);
        }

        move(promptY, 0);
        clrtoeol();  // Clear the whole line
        printw("Lash> %s", input.c_str());
        move(promptY, 6 + input.length());
        refresh();
    }

    return input;
}
