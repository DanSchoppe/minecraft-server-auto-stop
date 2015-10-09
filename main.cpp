#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include "config.h"

int main(int argc, const char* argv[])
{
  // Strategy:
  // Check whether TCP port 25565 (0x63DD) is in use
  // https://www.instructables.com/id/Make-Your-Minecraft-Server-Tell-You-When-Players-a/step3/Finding-Connected-Players-and-Making-a-Basic-Notif/

  /* -- No players connected: ---------------------
     ubuntu:~$ sudo cat /proc/net/tcp6
     sl  local_address                         remote_address                        st tx_queue rx_queue tr tm->when retrnsmt   uid  timeout inode
     0: 00000000000000000000000000000000:0016 00000000000000000000000000000000:0000 0A 00000000:00000000 00:00000000 00000000     0        0 8717 1 ################ 100 0 0 10 -1
     1: ################################:63DD 00000000000000000000000000000000:0000 0A 00000000:00000000 00:00000000 00000000   106        0 10299 1 ################ 100 0 0 10 -1
     ---------------------------------------------- */

  /* -- Player(s) connected: ----------------------
    ubuntu:~$ sudo cat /proc/net/tcp6
    sl  local_address                         remote_address                        st tx_queue rx_queue tr tm->when retrnsmt   uid  timeout inode
    0: 00000000000000000000000000000000:0016 00000000000000000000000000000000:0000 0A 00000000:00000000 00:00000000 00000000     0        0 8717 1 ################ 100 0 0 10 -1
    1: ################################:63DD 00000000000000000000000000000000:0000 0A 00000000:00000000 00:00000000 00000000   106        0 10299 1 ################ 100 0 0 10 -1
    2: ################################:63DD ################################:B51D 06 00000000:00000000 03:00000FE2 00000000     0        0 0 3 ################
    3: ################################:63DD ################################:B51E 01 00000030:00000000 00:00000000 00000000   106        0 26571 3 ################ 26 10 1 230 227
    ---------------------------------------------- */

  std::string tcp6_path("/proc/net/tcp6");
  std::ifstream tcp6(tcp6_path.data());

  if (!tcp6.is_open()) {
    std::cout << "Failed to open " << tcp6_path << std::endl;
    return 0;
  }

  std::string line,
              loc_addr, loc_port,
              rem_addr, rem_port;

  //                              local addr     port     remote addr    port
  std::regex reg(R"(\s*[0-9]+:\s*([0-9a-fA-F]+):(63DD)\s+([0-9a-fA-F]+):([0-9a-fA-F]+).*)");
  std::smatch groups;
  while(std::getline(tcp6, line)) {
    if (!std::regex_match(line, groups, reg)) continue;
    if (groups.size() != 5) continue;

    // Note: groups[0] contains full
    std::cout << "Match: " << groups[0] <<std::endl;

    int i = 0;
    loc_addr = groups[++i]; loc_port = groups[++i];
    rem_addr = groups[++i]; rem_port = groups[++i];

    std::cout << "Local:  " << loc_addr << ":" << loc_port << std::endl;
    std::cout << "Remote: " << rem_addr << ":" << rem_port << std::endl;
  }

  tcp6.close();
  return 0;
}
