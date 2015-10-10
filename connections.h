#ifndef __connections_h
#define __connections_h

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

static int connections(std::string path, std::string port) {
  std::ifstream tcp6(path.data());

  if (!tcp6.is_open()) {
    std::cout << "Failed to open " << path << std::endl;
    return 0;
  }

  std::string line,
    loc_addr, loc_port,
    rem_addr, rem_port;

  //                              local addr          port         remote addr    port
  std::regex reg(R"(\s*[0-9]+:\s*([0-9a-fA-F]+):()" + port + R"()\s+([0-9a-fA-F]+):([0-9a-fA-F]+).*)");
    //std::regex reg(R"(\s*[0-9]+:\s*([0-9a-fA-F]+):)(" + port + ")\s+([0-9a-fA-F]+):([0-9a-fA-F]+).*)");
  std::smatch groups;
  bool ret = false;
  while(std::getline(tcp6, line)) {
    if (!std::regex_match(line, groups, reg)) continue;
    if (groups.size() != 5) continue;
    ret = true;

    // Note: groups[0] contains full line
    std::cout << "Match: " << groups[0] <<std::endl;

    int i = 0;
    loc_addr = groups[++i]; loc_port = groups[++i];
    rem_addr = groups[++i]; rem_port = groups[++i];

    std::cout << "Local:  " << loc_addr << ":" << loc_port << std::endl;
    std::cout << "Remote: " << rem_addr << ":" << rem_port << std::endl;
  }

  tcp6.close();
  return ret;
}

#endif
