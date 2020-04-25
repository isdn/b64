#include <base64.h>
#include <iostream>

int main() {
  const std::string s = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";

  std::string encoded = Base64::encode(s);
  std::string decoded = Base64::decode(encoded);

  std::cout << "encoded: " << std::endl << encoded << std::endl << std::endl;
  std::cout << "decoded: " << std::endl << decoded << std::endl;

  return 0;
}

