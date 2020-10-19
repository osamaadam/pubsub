#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "Client.hpp"
#include "Server.hpp"
#define PORT 3030

int main() {
  int listening = socket(AF_INET, SOCK_STREAM, 0);
  if (listening == 0) {
    std::cerr << "Can't create socket\n";
    return -1;
  }

  Server serverObj = Server();
  sockaddr_in server = serverObj.getServer();

  if (bind(listening, (sockaddr *)&server, sizeof(server)) == -1) {
    std::cerr << "Can't bind to IP address\n";
    return -1;
  }

  if (listen(listening, SOMAXCONN) == -1) {
    std::cerr << "Can't listen\n";
    return -1;
  }

  Client clientObj = Client(listening);

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

  serverObj.listen(clientSocket);

  clientObj.closeConnection();
}
