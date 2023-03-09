#include <string>
#include <vector>

class Settings {
private:
  std::string serverIp;
  std::vector<std::string> nodesIp;
  void loadYamlFile(const std::string &filePath);

public:
  explicit Settings(const std::string filePath);
  std::string &getServerIp();
  std::vector<std::string> &getNodesIp();
};