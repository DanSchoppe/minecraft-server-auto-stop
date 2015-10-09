#include <iostream>

#include "config.h"

int main(int argc, const char* argv[])
{
  std::cout << "Version " << VERSION_MAJOR << "."
                          << VERSION_MINOR << std::endl;

  return 0;
}
