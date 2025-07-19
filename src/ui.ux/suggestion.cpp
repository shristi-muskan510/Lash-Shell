// suggestion.cpp
#include "../include/suggestion.hpp"
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <set>

using namespace std;

vector<string> loadAllSuggestions() {
    set<string> unique;  // to filter duplicates

    // 1. Built-in commands
    vector<string> builtins = {
        "ls", "cd", "cat", "clear", "echo", "exit", "mkdir", "rmdir",
        "rm", "touch", "sudo", "apt", "pwd"
    };
    unique.insert(builtins.begin(), builtins.end());

    // 2. Commands in PATH
    const char* pathEnv = getenv("PATH");
    if (pathEnv) {
        istringstream pathStream(pathEnv);
        string dir;
        while (getline(pathStream, dir, ':')) {
            DIR* d = opendir(dir.c_str());
            if (!d) continue;
            struct dirent* entry;
            while ((entry = readdir(d)) != nullptr) {
                if (entry->d_type == DT_REG || entry->d_type == DT_LNK || entry->d_type == DT_UNKNOWN) {
                    unique.insert(entry->d_name);
                }
            }
            closedir(d);
        }
    }

    // 3. From history
    ifstream hist(".lash_history");
    string line;
    while (getline(hist, line)) {
        unique.insert(line);
    }

    return vector<string>(unique.begin(), unique.end());
}

vector<string> fuzzySearch(const string& input, const vector<string>& pool) {
    vector<string> matches;
    for (const string& cmd : pool) {
        if (cmd.rfind(input, 0) == 0)  // only match if starts with input
            matches.push_back(cmd);
    }
    return matches;
}