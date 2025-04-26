#ifndef FLAG_HANDING
#define FLAG_HANDING

#include <getopt.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEMPLATE_CAPACYTY 2048

int change_flags(unsigned short *flags, char flag, char **template,
                 size_t *template_size);
void get_template_from_file(char *file_name, char **template,
                            size_t *template_size);
int parse_flag(int argc, char **argv, char **template, size_t *template_size,
               unsigned short *flags);
void add_to_template(char **template, size_t *template_size, char *str);

#endif