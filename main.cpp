#include <chrono>     // Time
#include <cstdlib>    // system()
#include <iostream>   // std::cout
#include <string>     // std::string
#include <thread>     // std::this_thread::sleep_for()

#include "config.h"
#include "connections.h"
#include "Opts.h"

int main(int argc, char* argv[]) {
  Opts opts;
  opts.getopt(argc, argv);

  /* Strategy:
     Check whether TCP port 25565 (0x63DD) is in use
     https://www.instructables.com/id/Make-Your-Minecraft-Server-Tell-You-When-Players-a/step3/Finding-Connected-Players-and-Making-a-Basic-Notif/

     -- No players connected: ---------------------
     ubuntu:~$ sudo cat /proc/net/tcp6
     sl  local_address                         remote_address                        st tx_queue rx_queue tr tm->when retrnsmt   uid  timeout inode
     0: 00000000000000000000000000000000:0016 00000000000000000000000000000000:0000 0A 00000000:00000000 00:00000000 00000000     0        0 8717 1 ################ 100 0 0 10 -1
     1: ################################:63DD 00000000000000000000000000000000:0000 0A 00000000:00000000 00:00000000 00000000   106        0 10299 1 ################ 100 0 0 10 -1
     ----------------------------------------------

     -- Player(s) connected: ----------------------
    ubuntu:~$ sudo cat /proc/net/tcp6
    sl  local_address                         remote_address                        st tx_queue rx_queue tr tm->when retrnsmt   uid  timeout inode
    0: 00000000000000000000000000000000:0016 00000000000000000000000000000000:0000 0A 00000000:00000000 00:00000000 00000000     0        0 8717 1 ################ 100 0 0 10 -1
    1: ################################:63DD 00000000000000000000000000000000:0000 0A 00000000:00000000 00:00000000 00000000   106        0 10299 1 ################ 100 0 0 10 -1
    2: ################################:63DD ################################:B51D 06 00000000:00000000 03:00000FE2 00000000     0        0 0 3 ################
    3: ################################:63DD ################################:B51E 01 00000030:00000000 00:00000000 00000000   106        0 26571 3 ################ 26 10 1 230 227
    ----------------------------------------------
  */

  using namespace std::chrono;
  using namespace std::this_thread;

  steady_clock::time_point start = steady_clock::now();
  typedef enum : uint8_t {
    Full = 0,
    Empty
  } ServerState;
  ServerState state = ServerState::Empty;

  for (;;) {
    if (connections(opts.file, opts.port)) {
      std::cout << "Connected clients detected" << std::endl;
      state = ServerState::Full;
    } else {
      switch (state) {
      case ServerState::Full:
        std::cout << "All clients have disconnected" << std::endl;
        start = steady_clock::now();
        state = ServerState::Empty;
        break;
      case ServerState::Empty:
        std::cout << "No clients detected" << std::endl;
        if (steady_clock::now() - start > std::chrono::seconds(opts.timeout)) {
          std::cout << "Shutting down the server" << std::endl;
          // TODO: Real networking instead of system()
          std::string wget = "wget " + opts.url;
          std::system(wget.data());
          return 0;
        }
        break;
      }
    }
    sleep_for(seconds(opts.interval));
  }

  return 0;
}
