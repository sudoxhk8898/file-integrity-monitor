#include "Scanner.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) { std::cout << "Usage: ./fim <directory>\n"; return 1; }

    auto files = Scanner::scanDirectory(argv[1]);
    for (const auto& [path, hash] : files)
        std::cout << hash << "  " << path << "\n";
    std::cout << "Total files: " << files.size() << "\n";
}
