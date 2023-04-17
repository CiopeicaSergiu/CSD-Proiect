#include "BlowFish.h"
#include "Service.h"
#include "Utilities.h"
#include <iostream>

const static std::wstring key{L"Bruh"};

int main() {
  // Service service(11420);
  // service.start();
  std::wstring text{L"Ana are mere."};
  std::wstring encryptedText;

  try {
    encryptedText = blowfish::encrypt(text, key);
  } catch (const std::exception &e) {
    std::cout << e.what() << "\n";
    std::cout << "Eception cought!!\n";
  }

  std::wcout << "Encrypted text: " << encryptedText << "\n";
  std::wcout << blowfish::dencrypt(encryptedText, key) << "\n";
  return 0;
}