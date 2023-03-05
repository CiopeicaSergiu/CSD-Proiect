#include "Server.h"
#include <memory>
#include <restbed>

std::string getData();

void Server::setEndPointForGetData(
    const std::make_shared<restbed::Resource> &resource,
    const std::string path) {
  resource->set_method_handler("GET", get_method_handler);
}

void Server::setEndPointForReceiveData(const std::string path) {}

void Server::configureEndPoints() {
  auto resource = std::make_shared<restbed::Resource>();
  setEndPointForGetData();
  setEndPointForReceiveData();
}

Server::Server(const size_t port);
void Server::start();
