#include "Opts.h"

#include <getopt.h>
#include <stdio.h>
#include <string>

// Source: http://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
int Opts::getopt(int argc, char* argv[]) {
  int c;

  while (1) {
    static struct option long_options[] =
      {
        /* These options set a flag. */
        // {"verbose", no_argument,       &verbose_flag, 1},
        // {"brief",   no_argument,       &verbose_flag, 0},
        /* These options don’t set a flag.
           We distinguish them by their indices. */
        // {"add",     no_argument,       0, 'a'},
        {"verbosity", required_argument, 0, 'v'},
        {"interval",  required_argument, 0, 'i'},
        {"timeout",   required_argument, 0, 't'},
        {"port",      required_argument, 0, 'p'},
        {"file",      required_argument, 0, 'f'},
        {"url",       required_argument, 0, 'u'},
        {0,           0,                 0,  0 }
      };

    /* getopt_long stores the option index here. */
    int option_index = 0;

    c = getopt_long(argc, argv, "q:t:p:f:u:i:v:",
                    long_options, &option_index);

    /* Detect the end of the options. */
    if (c == -1) break;

    switch (c) {
    case 0:
      /* If this option set a flag, do nothing else now. */
      if (long_options[option_index].flag != 0)
        break;
      printf ("option %s", long_options[option_index].name);
      if (optarg)
        printf (" with arg %s", optarg);
      printf ("\n");
      break;

    case 'v':
      verbosity = atoi(optarg);
      printf("option -v with value `%d'\n", verbosity);
      break;

    case 'i':
      interval = atoi(optarg);
      printf("option -i with value `%d'\n", interval);
      break;

    case 't':
      timeout = atoi(optarg);
      printf("option -t with value `%d'\n", timeout);
      break;

    case 'p':
      port = optarg;
      printf ("option -p with value `%s'\n", optarg);
      break;

    case 'f':
      file = optarg;
      printf ("option -f with value `%s'\n", optarg);
      break;

    case 'u':
      url = optarg;
      printf ("option -u with value `%s'\n", optarg);
      break;

    case '?':
      /* getopt_long already printed an error message. */
      break;

    default:
      abort ();
    }
  }

  /* Instead of reporting ‘--verbose’
     and ‘--brief’ as they are encountered,
     we report the final status resulting from them. */
  // if (verbose_flag)
  //   puts ("verbose flag is set");

  /* Print any remaining command line arguments (not options). */
  if (optind < argc) {
    printf ("non-option ARGV-elements: ");
    while (optind < argc)
      printf ("%s ", argv[optind++]);
    putchar ('\n');
  }

  return 0;
}
