#include "his.h"

void msg(char *file, const char *func, int line, const char *fmt, ...) {
  if (!verbose_g)
    return;

  fprintf(stderr, "%s:%s, line %d: ", basename(file), func, line);
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  fprintf(stderr, "\n");
}
