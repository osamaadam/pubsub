#include "includes.hpp"

class Server {
 private:
  sockaddr_in server;

 public:
  Server() {
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &server.sin_addr);
  }

  void listen(int clientSocket) {
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
  }

  sockaddr_in getServer() {
    return server;
  }
};
