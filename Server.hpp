#include <chrono>
#include <ctime>
#include <thread>

#include "includes.hpp"

class Server {
 private:
  sockaddr_in serverAddress;

  static void listenForInput(int clientSocket) {
    while (true) {
      char buffer[4096];
      int receivedPing = recv(clientSocket, buffer, 4096, 0);
      if (receivedPing) {
        std::time_t result = std::time(nullptr);
        send(clientSocket, strcat(std::asctime(std::localtime(&result)), "\n"), 26, 0);
        memset(buffer, 0, 4096);
      }
    }
  }

  static void listenIndefinitely(int clientSocket) {
    using namespace std::chrono_literals;
    using namespace std::this_thread;
    while (true) {
      std::time_t result = std::time(nullptr);
      send(clientSocket, strcat(std::asctime(std::localtime(&result)), "\n"), 26, 0);
      sleep_for(5s);
    }
  }

 public:
  Server() {
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &serverAddress.sin_addr);
  }

  void listen(int clientSocket) {
    std::cout << "Listening on port " << PORT << "\n";
    std::thread input(listenForInput, clientSocket);
    std::thread interval(listenIndefinitely, clientSocket);
    while (true) {
    }
  }

  sockaddr_in getAddress() {
    return serverAddress;
  }
};
