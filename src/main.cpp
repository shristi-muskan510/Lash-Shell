#include <iostream>
#include "../include/input.hpp"
#include "../include/execute.hpp"
#include "../include/history.hpp"
#include <ncurses.h>

using namespace std;

int main(){
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    loadHistory(".lash_history");

    while(1){
        printw("Lash>");
        refresh();

        string line = getInputWithHistory();
        string trimmed = trim(line);

        if(trimmed.empty()) continue;
        if(trimmed == "exit") break;

        addToHistory(trimmed);
        vector<string> args = parseInput(trimmed);
        executeCommand(args);  
    }
    
    endwin();
}