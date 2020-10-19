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

    // char* buffer = strcat(std::asctime(std::localtime(&result)), "\n");

    while (true) {
      std::time_t result = std::time(nullptr);
      // buffer = strcat(std::asctime(std::localtime(&result)), "\n");
      send(clientSocket, strcat(std::asctime(std::localtime(&result)), "\n"), 26, 0);
      std::cout << strcat(std::asctime(std::localtime(&result)), "\n");
      sleep_for(10s);
    }
  }

  sockaddr_in getServer() {
    return server;
  }
};
