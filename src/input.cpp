#include "../include/input.hpp"
#include "../include/history.hpp"
#include <termios.h>
#include <unistd.h>
#include <string>
#include <iostream>

using namespace std;

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
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

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

                    cout << "\33[2K\r";
                    cout << "\033[1;35mLash>\033[0m ";
                    cout << "\033[1;36m" << cwd << "\033[0m";
                    cout << " > " << input << flush;

                } else if (seq[1] == 'B') {  // ↓
                    input = getNextCommand();

                    cout << "\33[2K\r";
                    cout << "\033[1;35mLash>\033[0m ";
                    cout << "\033[1;36m" << cwd << "\033[0m";
                    cout << " > " << input << flush;
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