#ifndef FILE_PROCESSING
#define FILE_PROCESSING
#include <malloc.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int procces_file(char *path, unsigned short flags, regex_t reg, char multifile);
void print_only_matching(char *row, regex_t reg, unsigned short flags,
                         int line_number, int multifile, char *path);
void print_substr(char *row, regoff_t off, regoff_t len);
int set_flags(unsigned short flags);

#endif