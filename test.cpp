#include "Service.h"
#include "Settings.h"
int main() {
  Settings settings("settings.yaml");
  Service service(11420);
  service.start();
  return 0;
}