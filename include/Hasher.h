#pragma once
#include <string>

class Hasher {
public:
    static std::string sha256File(const std::string& path);
};
