#include "../include/input.hpp"
#include <cctype>
#include <sstream>

using namespace std;

string trim(const string& input){
    size_t start = input.find_first_not_of(" \t\n\r");
    size_t end = input.find_last_not_of(" \t\n\r");

    if(start == string::npos){
        return " ";
    }
    return input.substr(start, end-start+1);
}

vector<string> parseInput(const string& input) {
    vector<string> tokens;
    istringstream stream(input);
    string word;

    while(stream >> word){
        tokens.push_back(word);
    }
    return tokens;
}