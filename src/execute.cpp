#include "../include/execute.hpp"
#include "../include/signal.hpp"
#include "../include/history.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <input.hpp>

using namespace std;

int executeCommand(const vector <string>& args){
    if(args.empty())
       return 1;

    if(args[0] == "history"){
        int row = 1;
        ifstream file(".lash_history");
        string line;
        int index = 1;

        if(!file){
            cout << "No history file found!\n";
            exit(0);
        }

        while(getline(file, line)){
            cout << index++ << " " << line << "\n";
        }

        return 1;
    }
    
    //Checks for pipe
    bool hasPipe = false;
    for(const auto& arg : args){
        if(arg == "|"){
            hasPipe = true;
            break;
        }
    }

    //Checks for background process
    bool isBackground = false;
    vector<string> actualArgs = args;
    if(args.back() == "&"){
        isBackground = true;
        actualArgs.pop_back();
    }

    if(!hasPipe){
        //for adding cd
        if(args[0] == "cd"){
            if(args.size() < 2){
                cout << "cd: expected argument\n";
            }
            else{
                if(chdir(args[1].c_str()) != 0){
                    perror("cd failed!");
                }
            }
            return 1;
        }
    
        //Checking IO redirection
        vector<string> cleanedArgs;
        string inputFile = "", outputFile = "";
        bool redirectIn = false, redirectOut = false;

        for (size_t i = 0; i < args.size(); ++i) {
            if (args[i] == "<" && i + 1 < args.size()) {
                inputFile = args[i+1];
                redirectIn = true;
                ++i;
            }
            else if (args[i] == ">" && i + 1 < args.size()) {
                outputFile = args[i+1];
                redirectOut = true;
                ++i;
            }
            else {
                cleanedArgs.push_back(args[i]);
            }
        }

        //Converting string into char* array for execvp
        char* argv[cleanedArgs.size() + 1];
        for(size_t i=0; i<cleanedArgs.size(); ++i){
            argv[i] = const_cast<char*> (cleanedArgs[i].c_str());
        }
        argv[cleanedArgs.size()] = nullptr;

        //fork and execvp
        pid_t pid = fork();

        if(pid == 0){

            //Input redirection
            if (redirectIn) {
                int fd = open(inputFile.c_str(), O_RDONLY);
                if (fd < 0) {
                    perror("Input open failed");
                    exit(1);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
            }

            //Output redirection
            if (redirectOut) {
                int fd = open(outputFile.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("Output open failed");
                    exit(1);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }

            resetChildSignals();

            execvp(argv[0], argv);
            perror("Execvp failed!");
            exit(1);
        }
        else if(pid>0){
            if(!isBackground){
                int status;
                wait(nullptr);
                return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
            }
            else{
                cout << "[background pid " << pid << "]" << endl;
                return 0;
            }
        }
        else{
            perror("Fork failed");
        }
    }

    //If hasPipe is true
    else{
        vector<vector<string>> commands;
        vector<string> current;

        //split commands based on pipes
        for (const string& arg : args) {
            if (arg == "|") {
                commands.push_back(current);
                current.clear();
            } else {
                current.push_back(arg);
            }
        }
        if (!current.empty()) {
            commands.push_back(current);
        } 

        //creates pipe b/w two commands
        int numPipes = commands.size() - 1;
        int pipefd[2 * numPipes];

        for (int i = 0; i < numPipes; ++i) {
            pipe(pipefd + i * 2);
        }

        //fork for each command and execvp
        for (int i = 0; i < commands.size(); ++i) {

            disableRawMode();  // So child gets normal terminal
        
            pid_t pid = fork();
            if (pid == 0) {
                if (i > 0) {
                    dup2(pipefd[(i - 1) * 2], STDIN_FILENO);
                }
                if (i < numPipes) {
                    dup2(pipefd[i * 2 + 1], STDOUT_FILENO);
                }
                for (int j = 0; j < 2 * numPipes; ++j) 
                    close(pipefd[j]);

                vector<char*> argv;
                for (const auto& s : commands[i])
                argv.push_back(const_cast<char*>(s.c_str()));
                argv.push_back(nullptr);

                resetChildSignals();

                execvp(argv[0], argv.data());
                perror("execvp failed");
                exit(1);
            }
        }

        for (int i = 0; i < 2 * numPipes; ++i) 
            close(pipefd[i]);
        for (int i = 0; i < commands.size(); ++i){
            if(!isBackground){
                int status;
                wait(nullptr);
                return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
            }
            else{
                cout << "[background pid " << "]" << endl;
                return 0;
            }
        }
        enableRawMode();   // Restore raw mode before next prompt
    }
}