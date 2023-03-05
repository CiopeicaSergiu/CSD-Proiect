#include <string>

class Server {
private:
  void configureEndPoints();
  void setEndPointForGetData(const std::string path);
  void setEndPointForReceiveData(const std::string path);

public:
  Server(const size_t port);
  void start();
};