#include "Settings.h"
#include <iostream>
#include <yaml-cpp/yaml.h>

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
std::string &Settings::getServerIp() { return serverIp; }
std::vector<std::string> &Settings::getNodesIp() { return nodesIp; }
