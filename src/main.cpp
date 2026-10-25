#include "Scanner.h"
#include "Baseline.h"
#include "Reporter.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::string mode = (argc >= 2) ? argv[1] : "";

    if (mode == "init" && argc >= 4) {
        auto files = Scanner::scanDirectory(argv[2]);
        if (!Baseline::save(files, argv[3])) {
            std::cerr << "Cannot write baseline: " << argv[3] << "\n";
            return 1;
        }
        std::cout << "Baseline saved: " << files.size() << " files -> " << argv[3] << "\n";
        return 0;
    }

    if (mode == "check" && argc >= 4) {
        Baseline::FileMap baseline;
        if (!Baseline::load(baseline, argv[3])) {
            std::cerr << "Cannot read baseline: " << argv[3] << "\n";
            return 1;
        }
        auto current = Scanner::scanDirectory(argv[2]);
        int changes = Reporter::compare(baseline, current);
        return changes == 0 ? 0 : 2;
    }

    if (mode == "show" && argc >= 3) {
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
              << "  ./fim init  <directory> <baseline-file>\n"
              << "  ./fim check <directory> <baseline-file>\n"
              << "  ./fim show  <baseline-file>\n";
    return 1;
}
