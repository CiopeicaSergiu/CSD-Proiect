#include "BlowFish.h"
#include "Service.h"
#include "Utilities.h"
#include <iostream>

const static std::wstring key{L"Bruh"};

int main() {
  std::wstring text = utils::readFile("./data/test.txt");
  std::wstring encryptedText = blowfish::encrypt(text, key);
  std::string stringText = utils::to_string(encryptedText);
  std::wstring wstringText = utils::to_wstring(stringText);
  std::wcout << blowfish::dencrypt(encryptedText, key) << "\n";
  return 0;
}