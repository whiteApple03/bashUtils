#include "flag_handling.h"

#include "includs.h"

void add_to_template(char **template, size_t *template_size, char *str) {
  // if (str != NULL) {
  if (*template == NULL) {
    *template_size = TEMPLATE_CAPACYTY + strlen(str);
    *template = (char *)malloc(sizeof(char) * (*template_size));

    (*template)[0] = '\0';
    strcat(*template, str);
  } else {
    if (*template_size - strlen(*template) < strlen(str) + 1) {
      *template_size += TEMPLATE_CAPACYTY + strlen(str);
      *template = realloc(*template, *template_size);
    }
    strcat(*template, "|");
    strcat(*template, str);
  }
  // }
}

int change_flags(unsigned short *flags, char flag, char **template,
                 size_t *template_size) {
  int code = 0;
  switch (flag) {
    case 'e':
      add_to_template(template, template_size, optarg);
      break;
    case 'i':
      (*flags) = (*(flags) | (1 << 1));
      break;
    case 'v':
      (*flags) = (*(flags) | (1 << 2));
      break;
    case 'c':
      (*flags) = (*(flags) | (1 << 3));
      break;
    case 'l':
      (*flags) = (*(flags) | (1 << 4));
      break;
    case 'n':
      (*flags) = (*(flags) | (1 << 5));
      break;
    case 'h':
      (*flags) = ((*flags) | (1 << 6));
      break;
    case 's':
      (*flags) = ((*flags) | (1 << 7));
      break;
    case 'f':
      get_template_from_file(optarg, template, template_size);

      break;
    case 'o':
      (*flags) = ((*flags) | (1 << 9));
      break;
    default:
      code = -1;
      break;
  }
  return code;
}

void get_template_from_file(char *file_name, char **template,
                            size_t *template_size) {
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    perror(file_name);
  } else {
    char *expr = (char *)malloc(sizeof(char) * MAX_ROW_SIZE);
    char *template_from_file =
        (char *)malloc(sizeof(char) * (MAX_ROW_SIZE + 3));
    size_t template_size_file = MAX_ROW_SIZE + 3;
    template_from_file[0] = '\0';

    while (fgets(expr, MAX_ROW_SIZE, file) != NULL) {
      if (template_size_file - strlen(template_from_file) < strlen(expr) + 3) {
        template_size_file += MAX_ROW_SIZE + strlen(expr);
        template_from_file =
            (char *)realloc(template_from_file, template_size_file);
      }
      if (expr[0] == '\n') {
        strcat(template_from_file, "$|");
      } else {
        int expr_size = strlen(expr);

        if (expr[expr_size - 1] == '\n') {
          expr[expr_size - 1] = '\0';
        }
        strcat(template_from_file, expr);

        strcat(template_from_file, "|");
      }
    }

    if (template_from_file[strlen(template_from_file) - 1] == '|') {
      (template_from_file)[strlen(template_from_file) - 1] = '\0';
    }
    fclose(file);

    add_to_template(template, template_size, template_from_file);
    if (template_from_file != NULL) {
      free(template_from_file);
    }
    if (expr != NULL) free(expr);
  }
}

int parse_flag(int argc, char **argv, char **template, size_t *template_size,
               unsigned short *flags) {
  char res;
  int code = 0;
  while ((res = getopt(argc, argv, "e:icvnlhsf:o")) != -1) {
    if (change_flags(flags, res, template, template_size) == -1) {
      code = -1;
      break;
    }
  }
  return code;
}