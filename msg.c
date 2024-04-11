#include "his.h"

void msg(char *file, const char *func, int line, const char *fmt, ...) {
  fprintf(stderr, "%s:%s, line %d: ", basename(file), func, line);

  if (!verbose_g)
    return;

  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  fputc('\n', stderr);
  va_end(args);
}
