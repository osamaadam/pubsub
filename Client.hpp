#include "includes.hpp"

class Client {
 private:
  sockaddr_in client;
  socklen_t clientSize = sizeof(client);
  char host[NI_MAXHOST];
  char service[NI_MAXSERV];
  int clientSocket;

 public:
  Client(int listening) {
    clientSocket = accept(listening, (sockaddr *)&client, &clientSize);
    if (clientSocket == -1) {
      std::cerr << "Client can not connect.\n";
    }

    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
  };

  void closeConnection() {
    close(clientSocket);
  }

  sockaddr_in getClient() {
    return client;
  }

  socklen_t getClientSize() {
    return clientSize;
  }

  int getClientSocket() {
    return clientSocket;
  }

  char *getHost() {
    return (char *)host;
  }

  char *getService() {
    return (char *)service;
  }
};