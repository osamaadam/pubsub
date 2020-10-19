#include <iostream>
#include <string>

#include "Server.hpp"
#define PORT 3030

int main() {
  Server server = Server();
  server.doListen();
}
