#ifndef INCLUDS_H
#define INCLUDS_H
#define MAX_FILENAME_SIZE 256
#define MAX_ROW_SIZE 256
#define MAX_MATCH_SIZE 256

#define check_exec_res                      \
  (!(flags & (1 << 2)) && exec_res == 0) || \
      ((flags & (1 << 2)) && exec_res == REG_NOMATCH)

#endif