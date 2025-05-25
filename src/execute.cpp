#include "../include/execute.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void executeCommand(const vector <string>& args){
    if(args.empty())
       return;
    
    //Converting string into char* array for execvp
    char* argv[args.size() + 1];
    for(size_t i=0; i<args.size(); ++i){
        argv[i] = const_cast<char*> (args[i].c_str());
    }
    argv[args.size()] = nullptr;

    pid_t pid = fork();

    if(pid == 0){
        execvp(argv[0], argv);
        perror("Execvp failed!");
        exit(1);
    }
    else if(pid>0){
        wait(nullptr);
    }
    else{
        perror("Fork failed");
    }

}