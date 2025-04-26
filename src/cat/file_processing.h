#ifndef FILE_PROCESSING
#define FILE_PROCESSING
#include <stdio.h>
#include <stdlib.h>

void process_flags(unsigned char flags, int *empty_lines, char *new_line,
                   int *row_number, char *ch);
int display_file(char *path, unsigned char flags);

#endif