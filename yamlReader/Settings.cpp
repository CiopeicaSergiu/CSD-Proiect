#include "Settings.h"
#include </home/sergiu/Desktop/CSD/Proiect/dependencies/yaml/include/yaml-cpp/yaml.h>
#include <iostream>

void Settings::loadYamlFile(const std::string &filePath) {

  YAML::Node serverSettings = YAML::LoadFile(filePath);

  serverIp = serverSettings["serverIp"].as<std::string>();
  std::cout << serverIp << "\n";
  // serverSettings["nodesIp"].as<std::vector<std::string>>();
}

Settings::Settings(const std::string filePath) { loadYamlFile(filePath); }
