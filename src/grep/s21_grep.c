#include <getopt.h>
#include <malloc.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_processing.h"
#include "flag_handling.h"

int main(int argc, char *argv[]) {
  int code = 0;
  regex_t reg;
  unsigned short flags = 0;
  char *template = NULL;
  size_t template_size = 0;
  int reti = 0;
  char *reg_file_name = NULL;
  if (argc <= 2) {
    printf(
        "grep [OPTION...] PATTERNS [FILE...]\ngrep [OPTION...] -e PATTERNS "
        "... [FILE...]\ngrep [OPTION...] -f PATTERN_FILE ... [FILE...]\n");
    code = -1;
  } else {
    code = parse_flag(argc, argv, &template, &template_size, &flags);
  }

  if (code == 0) {
    if (template == NULL) {
      add_to_template(&template, &template_size, argv[optind++]);
    }
    char multifile = 0;
    if (argc - optind > 1) {
      multifile = 1;
    }
    if (template != NULL) {
      reti = regcomp(&reg, template, set_flags(flags) | REG_EXTENDED);
      if (reti) {
        char error_message[1024];
        regerror(reti, &reg, error_message, sizeof(error_message));
        fprintf(stderr, "Ошибка компиляции регулярного выражения: %s\n",
                error_message);
        code = 1;
      } else {
        for (; optind < argc; optind++) {
          procces_file(argv[optind], flags, reg, multifile);
        }
      }
    }
  }
  if (!reti) {
    regfree(&reg);
  }

  if (template != NULL) {
    free(template);
  }
  if (reg_file_name != NULL) {
    free(reg_file_name);
  }
  return code;
}