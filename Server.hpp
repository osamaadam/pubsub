#include <chrono>
#include <ctime>
#include <thread>

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
    using namespace std::chrono_literals;
    using namespace std::this_thread;
    std::time_t result = std::time(nullptr);
    char* buffer = strcat(std::asctime(std::localtime(&result)), "\n");

    while (true) {
      sleep_for(1s);
      send(clientSocket, buffer, strlen(buffer), 0);
      std::cout << buffer;
    }
  }

  sockaddr_in getServer() {
    return server;
  }
};
