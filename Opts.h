#ifndef __Opts_h
#define __Opts_h

#include <string>

class Opts {
public:
  int getopt(int argc, char* argv[]);

  // int verbose_flag;   // set by ‘--verbose’
  int verbosity = 1;
  std::string file = "/proc/net/tcp6";
  std::string port = "63DD";
  int timeout = 30;
  int interval = 5;
  std::string url = "www.google.com";
};

#endif
