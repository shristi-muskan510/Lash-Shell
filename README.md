# Lash: A Minimal, Smart Shell
Lash is a lightweight, user-friendly shell written in C++. It features intelligent command suggestions, history navigation, aliases, and support for piping, redirection, and background jobs.
(This version works on MacOS only)

## Features
- **Fuzzy Suggestions**: Real-time suggestions from commands, '$PATH', and history.
- **Arrow Key Navigation**: Cycle through suggestions and history with arrow keys.
- **Command History**: Auto-saved and loaded from '.lash_history'.
- **Aliases Support**:  Customize shortcuts via '.lashrc'.
- **Background Jobs**: Support for '&' to run background processes.
- **Pipes & Redirection**: Use '|', '>', '<' like regular shells.
- **Minimal C++ Codebase**: Built from scratch without ncurses or heavy libraries.

## Installation Instruction:
1. Download the Latest release: 
wget https://github.com/shristi-muskan510/Lash-Shell/releases/download/v1.0.0/lash-v1.0.tar.gz
2. Extract and install: 
tar -xvzf lash-v1.0.tar.gz
cd lash
./install.sh
3. Then run: ./lash

## Configuration:
You can add aliases and customization in your home directory under ~./lashrc

## Usage tips:
* Use arrow keys up/down to navigate history and left/right to navigate suggestions.
* Start typing to get suggestions.
* Use 'tab' to select the suggestion and 'return' to run the command.
* Use &, |, <, > as you would in Bash or Zsh.
* Type alias to view current alias.

## Notes:
- Currently tested and stable on macOS.
- Linux support (v1.1) in progress.

## License: 
MIT License

## Author:
**Shirti Muskan**
