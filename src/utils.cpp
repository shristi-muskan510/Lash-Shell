#include "../include/utils.hpp"
#include <sstream>

using namespace std;

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