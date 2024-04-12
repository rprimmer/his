#include "his.h"

void *xcalloc(size_t sz) {
  void *ret;

  if (! (ret = calloc(1, sz)) )
    error("out of memory (while allocating %d bytes)", sz);
  
  return ret;
}
