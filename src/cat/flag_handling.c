#include "flag_handling.h"

#include <getopt.h>
#include <stdlib.h>

int change_flags(unsigned char *flags, char res) {
  int code = 0;
  switch (res) {
    case 'B':
    case 'b':
      (*flags) = (*(flags) | 1);
      break;
    case 'E':
      (*flags) = (*(flags) | (1 << 1));
      break;
    case 'N':
    case 'n':
      (*flags) = (*(flags) | (1 << 2));
      break;
    case 'S':
    case 's':
      (*flags) = (*(flags) | (1 << 3));
      break;
    case 'T':
      (*flags) = (*(flags) | (1 << 4));
      break;
    case 'v':
      (*flags) = (*(flags) | (1 << 5));
      break;
    case 'e':
      (*flags) = (*(flags) | (1 << 1));
      (*flags) = (*(flags) | (1 << 5));
      break;
    case 't':
      (*flags) = (*(flags) | (1 << 4));
      (*flags) = (*(flags) | (1 << 5));
      break;
    default:
      code = -1;
      break;
  }
  return code;
}

int parse_flags(int argc, char **argv, unsigned char *flags) {
  struct option longopts[] = {{"number-nonblank", no_argument, NULL, 'B'},
                              {"number", no_argument, NULL, 'N'},
                              {"squeeze-blank", no_argument, NULL, 'S'},
                              {NULL, 0, NULL, 0}};
  char res;
  int code = 0;
  while ((res = getopt_long(argc, argv, "EetbnsTvBNS", longopts, NULL)) != -1) {
    if (change_flags(flags, res) == -1) {
      code = -1;
      break;
    }
  }
  return code;
}