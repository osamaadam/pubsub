#include <string>
#include <thread>

#include "includes.hpp"
class Client {
 private:
  int sock = 0, valread;
  std::string line;
  struct sockaddr_in serv_addr;
  char buffer[1024] = {0};
  int clientSocket;

  static void listenForSocket(int sock, char buffer[]) {
    while (true) {
      int valread = read(sock, buffer, 1024);
      if (valread) {
        std::cout << (buffer);
      }
    }
  }

 public:
  Client() {
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      throw std::runtime_error("\n Socket creation error \n");
      // make an error here
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
      throw std::runtime_error("\n Invalid address/ Address not supported \n");
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
      throw std::runtime_error("\nConnection Failed \n");
    }
  };

  sockaddr_in getClient() {
    return serv_addr;
  }

  void readData() {
    std::thread interval(listenForSocket, sock, buffer);
    while (true) {
      getline(std::cin, line);
      if (line.empty() || !line.empty()) {
        send(sock, "REQUEST", strlen("REQUEST"), 0);
      }
    }
  }
};