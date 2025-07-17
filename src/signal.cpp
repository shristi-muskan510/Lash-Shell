#include "signal.hpp"
#include <csignal>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void handleSigInt(int sig) {
    cout << "\n";
    cout << "\033[1;35mLash>\033[0m " << flush;
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