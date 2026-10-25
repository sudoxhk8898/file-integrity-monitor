#pragma once
#include <string>
#include <unordered_map>

class Baseline {
public:
    using FileMap = std::unordered_map<std::string, std::string>;

    // Writes "hash  path" lines to file. Returns false on failure.
    static bool save(const FileMap& files, const std::string& baselineFile);

    // Reads baseline file into files. Returns false on failure.
    static bool load(FileMap& files, const std::string& baselineFile);
};
