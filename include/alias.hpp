#pragma once
#include <string>
#include <vector>
#include <unordered_map>

void addAlias(const std:: string& name, const std::string& value);
void showAlias();
std::vector<std::string> resolveAlias(std::vector<std::string> args);
