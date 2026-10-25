#include "Baseline.h"
#include <fstream>

bool Baseline::save(const FileMap& files, const std::string& baselineFile) {
    std::ofstream out(baselineFile);
    if (!out) return false;
    for (const auto& [path, hash] : files)
        out << hash << "  " << path << "\n";
    return true;
}

bool Baseline::load(FileMap& files, const std::string& baselineFile) {
    std::ifstream in(baselineFile);
    if (!in) return false;
    files.clear();

    std::string line;
    while (std::getline(in, line)) {
        // hash is 64 chars, then 2 spaces, then the path
        if (line.size() <= 66) continue;
        files[line.substr(66)] = line.substr(0, 64);
    }
    return true;
}
