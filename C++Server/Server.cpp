#include "Server.h"

void Server::sendResponseAndCloseSession(
    const std::shared_ptr<restbed::Session> &session,
    const std::string message) {

  session->close(restbed::OK, message,
                 {{"Content-Length", std::to_string(message.size()).c_str()}});
}

void Server::sendUnfoundAndCloseSession(
    const std::shared_ptr<restbed::Session> &session,
    const std::string message) {
  session->close(restbed::UNAUTHORIZED,
                 {{"Content-Length", std::to_string(message.size()).c_str()}});
}

void Server::setSettings() {
  settings = std::make_shared<restbed::Settings>();
  settings->set_port(port);
  settings->set_default_header("Connection", "close");
}

Server::Server(const size_t port) { this->port = port; }

void Server::start() {
  resource = std::make_shared<restbed::Resource>();

  configureEndpoints();
  setSettings();

  restbed::Service service;
  service.publish(resource);
  service.start(settings);
}
