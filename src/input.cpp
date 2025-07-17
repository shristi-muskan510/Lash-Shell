#include "../include/input.hpp"
#include "../include/history.hpp"
#include <termios.h>
#include <unistd.h>
#include <string>
#include <iostream>

static struct termios originalTermios;

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

std::string getInputLine() {
    enableRawMode();

    std::string input;
    char c;

    while (read(STDIN_FILENO, &c, 1) == 1) {
        if (c == '\n') {
            std::cout << "\n";
            break;
        } else if (c == 127 || c == 8) {  // backspace
            if (!input.empty()) {
                input.pop_back();
                std::cout << "\b \b" << std::flush;
            }
        } else if (c == 27) {
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) != 1) break;
            if (read(STDIN_FILENO, &seq[1], 1) != 1) break;

            if (seq[0] == '[') {
                if (seq[1] == 'A') {  // ↑
                    input = getPrevCommand();
                    std::cout << "\r\033[K\033[1;35mlash>\033[0m " << input << std::flush;
                } else if (seq[1] == 'B') {  // ↓
                    input = getNextCommand();
                    std::cout << "\r\033[K\033[1;35mlash>\033[0m " << input << std::flush;
                }
            }
        } else {
            input += c;
            std::cout << c << std::flush;  // Show typed char
        }
    }

    disableRawMode();
    return input;
}