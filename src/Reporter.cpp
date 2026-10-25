#include "Reporter.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int Reporter::compare(const Baseline::FileMap& baseline,
                      const Baseline::FileMap& current) {
    std::vector<std::string> modified, added, deleted;

    for (const auto& [path, hash] : current) {
        auto it = baseline.find(path);
        if (it == baseline.end())
            added.push_back(path);
        else if (it->second != hash)
            modified.push_back(path);
    }
    for (const auto& [path, hash] : baseline) {
        if (current.find(path) == current.end())
            deleted.push_back(path);
    }

    std::sort(modified.begin(), modified.end());
    std::sort(added.begin(), added.end());
    std::sort(deleted.begin(), deleted.end());

    for (const auto& p : modified) std::cout << "[MODIFIED] " << p << "\n";
    for (const auto& p : added)    std::cout << "[NEW]      " << p << "\n";
    for (const auto& p : deleted)  std::cout << "[DELETED]  " << p << "\n";

    int total = modified.size() + added.size() + deleted.size();
    if (total == 0)
        std::cout << "OK: no changes detected.\n";
    else
        std::cout << "Changes: " << modified.size() << " modified, "
                  << added.size() << " new, "
                  << deleted.size() << " deleted\n";
    return total;
}
