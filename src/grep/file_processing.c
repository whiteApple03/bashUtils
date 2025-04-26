#include "file_processing.h"

#include "includs.h"
int set_flags(unsigned short flags) {
  int res = 0;
  if (flags & (1 << 1)) {
    res |= REG_ICASE;
  }
  return res;
}

void print_substr(char *row, regoff_t off, regoff_t len) {
  for (int i = off, k = 0; k < len; k++, i++) {
    printf("%c", row[i]);
  }
  printf("\n");
}

void print_only_matching(char *row, regex_t reg, unsigned short flags,
                         int line_number, int multifile, char *path) {
  regmatch_t pmatch[1];
  regoff_t off, len;
  char *substr = row;
  int exec_res = regexec(&reg, substr, 1, pmatch, 0);
  int template_is_found = check_exec_res;

  off = pmatch[0].rm_so + (substr - row);
  len = pmatch[0].rm_eo - pmatch[0].rm_so;
  if (len != 0 && template_is_found) {
    while (len != 0 && template_is_found) {
      if (!(flags & (1 << 6)) && multifile) {
        printf("%s:", path);
      }
      if (flags & (1 << 5)) {
        printf("%d:", line_number);
      }
      print_substr(row, off, len);

      substr += pmatch[0].rm_eo;
      exec_res = regexec(&reg, substr, 1, pmatch, 0);
      template_is_found = check_exec_res;

      off = pmatch[0].rm_so + (substr - row);
      len = pmatch[0].rm_eo - pmatch[0].rm_so;
    }
  }
}

int actions_with_flags(regex_t reg, unsigned short flags, char *row, char *path,
                       int *number_of_rows, int multifile, int line_number,
                       int template_is_found) {
  int code = 0;
  if (template_is_found) {
    (*number_of_rows)++;
  }
  if ((flags & (1 << 4)) && template_is_found) {
    printf("%s\n", path);
    code = 1;
  }
  if (!code && !(flags & (1 << 3)) && template_is_found) {
    if (flags & (1 << 9)) {
      print_only_matching(row, reg, flags, line_number, multifile, path);
    } else {
      if (!(flags & (1 << 6)) && multifile) {
        printf("%s:", path);
      }
      if (flags & (1 << 5)) {
        printf("%d:", line_number);
      }
      printf("%s\n", row);
    }
  }
  return code;
}

int procces_file(char *path, unsigned short flags, regex_t reg,
                 char multifile) {
  int code = 0;
  char *row = (char *)malloc(sizeof(char) * MAX_ROW_SIZE);

  FILE *file = fopen(path, "r");
  if (file == NULL) {
    if (!(flags & (1 << 7))) perror(path);
    code = 1;
  }
  int number_of_rows = 0;
  int line_number = 1;
  size_t size = MAX_ROW_SIZE;
  while (!code && getline(&row, &size, file) != EOF) {
    char *newline;
    if ((newline = strrchr(row, '\n')) != NULL) {
      row[newline - row] = '\0';
    }

    int exec_res = regexec(&reg, row, 0, NULL, 0);
    int template_is_found = check_exec_res;
    if (actions_with_flags(reg, flags, row, path, &number_of_rows, multifile,
                           line_number, template_is_found)) {
      break;
    }
    line_number++;
  }
  if (!code && !(flags & (1 << 4)) && flags & (1 << 3)) {
    if (!(flags & (1 << 6)) && multifile) {
      printf("%s:", path);
    }
    printf("%d\n", number_of_rows);
  }
  if (row != NULL) {
    free(row);
  }
  if (code != 1) fclose(file);

  return code;
}