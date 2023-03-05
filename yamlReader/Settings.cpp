#include "Settings.h"
#include </home/sergiu/Desktop/CSD/Proiect/dependencies/yaml/include/yaml-cpp/yaml.h>
#include <iostream>

template <typename T> void printArray(const std::vector<T> &arr) {
  std::cout << "\nArr: ";
  for (const auto &el : arr) {
    std::cout << el << ", ";
  }
  std::cout << "\n";
}

void Settings::loadYamlFile(const std::string &filePath) {

  YAML::Node serverSettings = YAML::LoadFile(filePath);

  serverIp = serverSettings["serverIp"].as<std::string>();
  std::cout << serverIp << "\n";
  nodesIp = serverSettings["nodesIp"].as<std::vector<std::string>>();

  printArray(nodesIp);
}

Settings::Settings(const std::string filePath) { loadYamlFile(filePath); }
