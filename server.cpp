#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>
#define PORT 3030

int main() {
  int listening = socket(AF_INET, SOCK_STREAM, 0);
  if (listening == 0) {
    std::cerr << "Can't create socket\n";
    return -1;
  }

  sockaddr_in hint;
  hint.sin_family = AF_INET;
  hint.sin_port = htons(PORT);
  inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

  if (bind(listening, (sockaddr *)&hint, sizeof(hint)) == -1) {
    std::cerr << "Can't bind to IP address\n";
    return -1;
  }

  if (listen(listening, SOMAXCONN) == -1) {
    std::cerr << "Can't listen\n";
    return -1;
  }

  sockaddr_in client;
  socklen_t clientSize = sizeof(client);
  char host[NI_MAXHOST];
  char service[NI_MAXSERV];

  int clientSocket = accept(listening, (sockaddr *)&client, &clientSize);

  if (clientSocket == -1) {
    std::cerr << "Client can not connect.\n";
    return -1;
  }

  close(listening);

  memset(host, 0, NI_MAXHOST);
  memset(service, 0, NI_MAXSERV);

  int result =
    getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0);

  if (result) {
    std::cout << host << " connected to " << service << "\n";
  } else {
    inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
    std::cout << host << " connected to " << ntohs(client.sin_port) << "\n";
  }

  char buffer[4096];

  while (true) {
    memset(buffer, 0, 4096);
    int byteReceived = recv(clientSocket, buffer, 4096, 0);
    if (byteReceived == -1) {
      std::cerr << "Byte not received!\n";
      break;
    }

    if (byteReceived == 0) {
      std::cout << "Client disconnected\n";
      break;
    }

    std::cout << "Received: " << std::string(buffer, 0, byteReceived) << "\n";

    send(clientSocket, buffer, byteReceived + 1, 0);
  }

  close(clientSocket);
}
