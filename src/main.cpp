#include <iostream>
#include "../include/input.hpp"
#include "../include/execute.hpp"

using namespace std;

int main(){
    string input;

    while(1){
        cout << "Lash> ";
        getline(cin, input);

        input = trim(input);
        if(input == "exit")
           break;
        if(input.empty())
           continue;
        
        vector <string> args = parseInput(input);
        executeCommand(args);
    }

    return 0;
}