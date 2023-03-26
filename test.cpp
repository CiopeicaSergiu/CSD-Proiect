#include "BlowFish.h"
#include "Service.h"
#include "Utilities.h"
#include <iostream>

int main() {
  // Service service(11420);
  // service.start();
  std::wstring text{L"Ana are mere."};
  const auto encryptedText = blowfish::encrypt(text);
  std::wcout << "Encrypted text: " << encryptedText << "\n";
  std::wcout << blowfish::dencrypt(encryptedText) << "\n";
  return 0;
}