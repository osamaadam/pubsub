#include <iostream>
#include <string>

#include "Client.hpp"
#include "Server.hpp"
#define PORT 3030

int main() {
  const int listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (listeningSocket == 0) {
    std::cerr << "Can't create socket\n";
    return -1;
  }

  Server server = Server();
  sockaddr_in serverAddress = server.getAddress();

  const int boundSocket = bind(listeningSocket, (sockaddr *)&serverAddress, sizeof(serverAddress));

  if (boundSocket == -1) {
    std::cerr << "Can't bind to IP address\n";
    return -1;
  }

  const int app = listen(listeningSocket, SOMAXCONN);

  if (app == -1) {
    std::cerr << "Can't listen\n";
    return -1;
  }

  Client clientObj = Client(listeningSocket);

  sockaddr_in client = clientObj.getClient();
  char *host = clientObj.getHost();
  char *service = clientObj.getService();
  int clientSocket = clientObj.getClientSocket();

  int result =
    getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0);

  if (result) {
    std::cout << host << " connected to " << service << "\n";
  } else {
    inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
    std::cout << host << " connected to " << ntohs(client.sin_port) << "\n";
  }

  server.listen(clientSocket);

  clientObj.closeConnection();
}
