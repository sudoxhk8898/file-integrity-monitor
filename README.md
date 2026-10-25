# File Integrity Monitor (FIM)

A command-line tool written in C++17 that detects unauthorized changes to files.
It records a SHA-256 baseline of a directory and later reports which files were
modified, added, or deleted.

## How it works
1. `init` scans a directory recursively and saves a baseline of `hash  path` lines.
2. `check` rescans the directory and compares it against the baseline.

## Build
Requires g++ (C++17) and OpenSSL development headers.

    sudo apt install build-essential libssl-dev
    g++ -std=c++17 -Iinclude src/*.cpp -lssl -lcrypto -o fim

## Usage
    ./fim init  <directory> <baseline-file>
    ./fim check <directory> <baseline-file>
    ./fim show  <baseline-file>

Exit codes for `check`: 0 = no changes, 2 = changes found, 1 = error.

## Example
    $ ./fim init testdir baseline.txt
    Baseline saved: 2 files -> baseline.txt
    $ ./fim check testdir baseline.txt
    [MODIFIED] testdir/a.txt
    [NEW]      testdir/c.txt
    [DELETED]  testdir/sub/b.txt
    Changes: 1 modified, 1 new, 1 deleted

## Design
- `Hasher`: streams files in 4 KB chunks through OpenSSL EVP (SHA-256)
- `Scanner`: recursive traversal with `std::filesystem`
- `Baseline`: save/load of an `unordered_map<path, hash>`
- `Reporter`: compares two maps and prints sorted differences

## Limitations
The baseline file itself is not protected. An attacker who can edit it can hide
changes, so it should be stored read-only or on separate media.

## Ethical use
Use only on files and systems you own or have permission to monitor.
