#include "signal.hpp"
#include <csignal>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

using namespace std;

void handleSigInt(int sig) {
    cout << "\n";
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    cout << "\033[1;35mLash>\033[0m ";
    cout << "\033[1;36m" << cwd << "\033[0m";
    cout << " > " << flush;
}

// Setup signal handling for shell itself
void setupShellSignals() {
    signal(SIGINT, handleSigInt);
    // signal(SIGTSTP);
    // signal(SIGCHLD);
    // signal(SIGTERM);
    // signal(SIGQUIT)
}

// Called in child processes to allow them to die on Ctrl+C
void resetChildSignals() {
    signal(SIGINT, SIG_DFL);
}