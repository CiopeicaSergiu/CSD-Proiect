#include "Server.h"

class Service : public Server {
private:
  void
  setEndPointForGetData(const std::shared_ptr<restbed::Resource> &resource);

  void getDataEvent(const std::shared_ptr<restbed::Session> session);
  void configureEndpoints();

public:
  explicit Service(const size_t port) : Server(port){};
};