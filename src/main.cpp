#include "Scanner.h"
#include "Baseline.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc >= 4 && std::string(argv[1]) == "init") {
        auto files = Scanner::scanDirectory(argv[2]);
        if (!Baseline::save(files, argv[3])) {
            std::cerr << "Cannot write baseline: " << argv[3] << "\n";
            return 1;
        }
        std::cout << "Baseline saved: " << files.size() << " files -> " << argv[3] << "\n";
        return 0;
    }

    if (argc >= 3 && std::string(argv[1]) == "show") {
        Baseline::FileMap files;
        if (!Baseline::load(files, argv[2])) {
            std::cerr << "Cannot read baseline: " << argv[2] << "\n";
            return 1;
        }
        for (const auto& [path, hash] : files)
            std::cout << hash << "  " << path << "\n";
        std::cout << "Total files: " << files.size() << "\n";
        return 0;
    }

    std::cout << "Usage:\n"
              << "  ./fim init <directory> <baseline-file>\n"
              << "  ./fim show <baseline-file>\n";
    return 1;
}
