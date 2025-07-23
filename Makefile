# Makefile
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall

SRC_DIR = src
OBJ_DIR = obj
BIN = lash

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

$(BIN): $(OBJS)
	$(CXX) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN)