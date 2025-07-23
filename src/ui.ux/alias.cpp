#include "../include/alias.hpp"
#include "../include/input.hpp"
#include <iostream>
#include <sstream>

using namespace std;

unordered_map<string, string> aliasMap;

void addAlias(const string& name, const string& value){
    aliasMap[name] = value;
}

void showAlias(){
    for (auto& [k, v] : aliasMap) {
        std::cout << "alias " << k << "=\"" << v << "\"" << std::endl;
    }
}

vector<string> resolveAlias(vector<string> args) {
    if (!args.empty() && aliasMap.count(args[0])) {
        string expanded = aliasMap[args[0]];
        vector<string> expandedTokens = parseInput(expanded);
        // Replace first arg with expanded alias
        args.erase(args.begin());
        args.insert(args.begin(), expandedTokens.begin(), expandedTokens.end());
    }
    return args;
}

