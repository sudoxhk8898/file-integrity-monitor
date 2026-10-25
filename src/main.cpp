#include "Hasher.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) { std::cout << "Usage: ./fim <file>\n"; return 1; }
    std::cout << Hasher::sha256File(argv[1]) << "\n";
}
