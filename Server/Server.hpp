#include <chrono>
#include <ctime>
#include <thread>

#include "includes.hpp"

class Server {
 private:
  int server_fd, new_socket, valread;
  struct sockaddr_in serverAddress;
  int opt = 1;
  int addrlen = sizeof(serverAddress);
  char buffer[1024] = {0};

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
      sleep_for(10s);
    }
  }

 public:
  Server() {
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
      perror("socket failed");
      exit(EXIT_FAILURE);
    }
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
      perror("setsockopt");
      exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
      perror("bind failed");
      exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
      perror("listen");
      exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&serverAddress, (socklen_t *)&addrlen))
        < 0) {
      perror("accept");
      exit(EXIT_FAILURE);
    }
  }

  void doListen() {
    std::cout << "Listening on port " << PORT << "\n";
    std::thread input(listenForInput, new_socket);
    std::thread interval(listenIndefinitely, new_socket);
    while (true) {
    }
  }
};
