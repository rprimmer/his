#include "his.h"

// TODO Refactor to show include TU & __func__
void msg(char const *fmt, ...) {
  if (!verbose_g)
    return;

  va_list args;
  va_start(args, fmt);
  fprintf(stderr, "his debug: ");
  vfprintf(stderr, fmt, args);
  fputc('\n', stderr);
  va_end(args);
}
