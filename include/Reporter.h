#pragma once
#include "Baseline.h"

class Reporter {
public:
    // Prints differences between baseline and current scan.
    // Returns the number of changes found.
    static int compare(const Baseline::FileMap& baseline,
                       const Baseline::FileMap& current);
};
