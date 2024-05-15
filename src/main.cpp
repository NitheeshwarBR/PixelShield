#include "decryption.h"
#include "encryption.h"
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 4) {
    std::cerr
        << "Usage: " << argv[0]
        << " <encrypt/decrypt> <input/output filename> <output base/input base>"
        << std::endl;
    return 1;
  }

  std::string mode = argv[1];
  std::string filename = argv[2];
  std::string base = argv[3];

  if (mode == "encrypt") {
    encryptText(filename, base);
  } else if (mode == "decrypt") {
    decryptImages(base, filename);
  } else {
    std::cerr << "Invalid mode specified. Use 'encrypt' or 'decrypt'."
              << std::endl;
    return 1;
  }

  return 0;
}
