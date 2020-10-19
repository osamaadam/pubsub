#include <iostream>
#include <string>

#include "Client.hpp"

#define PORT 3030

int main() {
  Client clientObj = Client();
  clientObj.readData();
}
