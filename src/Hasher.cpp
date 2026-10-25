#include "Hasher.h"
#include <openssl/evp.h>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>

std::string Hasher::sha256File(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) return "";

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);

    std::vector<char> buffer(4096);
    while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
        EVP_DigestUpdate(ctx, buffer.data(), file.gcount());
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int len = 0;
    EVP_DigestFinal_ex(ctx, hash, &len);
    EVP_MD_CTX_free(ctx);

    std::ostringstream out;
    for (unsigned int i = 0; i < len; i++)
        out << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    return out.str();
}
