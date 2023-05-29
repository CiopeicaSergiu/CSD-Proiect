#include <memory>
#include <restbed>
#include <string>

namespace boost::json {
class value;
}

class Server {
protected:
  std::shared_ptr<restbed::Resource> resource;

  void
  sendResponseAndCloseSession(const std::shared_ptr<restbed::Session> &session,
                              const boost::json::value &dataValue);

  void
  sendUnfoundAndCloseSession(const std::shared_ptr<restbed::Session> &session,
                             const std::wstring message);

  explicit Server(const size_t port);

private:
  std::shared_ptr<restbed::Settings> settings;
  size_t port;

  virtual void configureEndpoints() = 0;

  void setSettings();

  // delete all the assignement operators and all Constructors that aren`t used

public:
  void start();
};