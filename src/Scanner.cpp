#include "Scanner.h"
#include "Hasher.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

std::unordered_map<std::string, std::string> Scanner::scanDirectory(const std::string& dir) {
    std::unordered_map<std::string, std::string> result;

    for (const auto& entry : fs::recursive_directory_iterator(
             dir, fs::directory_options::skip_permission_denied)) {
        if (!entry.is_regular_file()) continue;

        std::string path = entry.path().string();
        std::string hash = Hasher::sha256File(path);

        if (hash.empty()) {
            std::cerr << "Skipped (cannot read): " << path << "\n";
            continue;
        }
        result[path] = hash;
    }
    return result;
}
