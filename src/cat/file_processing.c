#include "file_processing.h"

void process_flags(unsigned char flags, int *empty_lines, char *new_line,
                   int *row_number, char *ch) {
  if ((*new_line) && (*ch) != '\n') {
    (*empty_lines) = 0;
  } else if ((*new_line) && (*ch) == '\n') {
    (*empty_lines) = 1;
  }
  if (flags & (1 << 2) && (*new_line)) {
    printf("%6d\t", *row_number);
  }
  if (flags & 1 && (*new_line) && !(*empty_lines)) {
    printf("%6d\t", *row_number);
  }
  if ((*ch) != '\n') {
    (*new_line) = 0;
  } else {
    (*new_line) = 1;
    if (flags & 1 && !(*empty_lines)) {
      (*row_number)++;
    } else if ((flags & (1 << 2))) {
      (*row_number)++;
    }
  }
  if (flags & (1 << 1) && (*ch) == '\n') {
    printf("$");
  }
  if (flags & (1 << 4) && (*ch) == '\t') {
    printf("^");
    (*ch) += 64;
  }
  if (flags & (1 << 5) && (*ch) >= 0 && (*ch) <= 31 && (*ch) != '\n' &&
      (*ch) != '\t') {
    printf("^");
    (*ch) += 64;
  }
}

int display_file(char *path, unsigned char flags) {
  FILE *file = fopen(path, "r");
  static int code = 0;
  if (file == NULL) {
    perror(path);
    code = -1;
  } else {
    static int row_number = 1;
    static int empty_lines = 0;
    char ch;
    static char new_line = 1;
    while ((ch = fgetc(file)) != EOF) {
      if (flags & (1 << 3)) {
        if (empty_lines && ch == '\n') {
          continue;
        }
      }
      process_flags(flags, &empty_lines, &new_line, &row_number, &ch);

      printf("%c", ch);
    }
    fclose(file);
  }
  return code;
}