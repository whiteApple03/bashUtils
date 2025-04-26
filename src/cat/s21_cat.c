#include <getopt.h>
#include <stdio.h>
#include <unistd.h>

#include "file_processing.h"
#include "flag_handling.h"

extern char *optarg;
extern int optind;

int main(int argc, char **argv) {
  int code = 0;
  unsigned char flags = 0;

  code = parse_flags(argc, argv, &flags);
  if (code == 0) {
    if ((flags & (1)) && (flags & (1 << 2))) {
      flags = flags & (~(1 << 2));
    }
    if (optind == argc) {
      printf("enter file\n");
      code = -1;
    } else {
      for (; optind < argc; optind++) {
        display_file(argv[optind], flags);
      }
    }
  }
  return code;
}