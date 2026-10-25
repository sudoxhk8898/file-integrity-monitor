#pragma once
#include <string>
#include <unordered_map>

class Scanner {
public:
    // Returns map of file path -> SHA-256 for every regular file under dir
    static std::unordered_map<std::string, std::string> scanDirectory(const std::string& dir);
};
