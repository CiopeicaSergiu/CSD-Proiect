#include "Service.h"
#include "Settings.h"
#include "Utilities.h"
#include <iostream>

int main() {
  const std::string text = utils::readFromFile("./C++Server/testFile.txt");
  std::cout << text << "\n";
  Settings settings("settings.yaml");
  Service service(11420);
  service.start();
  return 0;
}