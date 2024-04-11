#include "his.h"

void *xmalloc(size_t sz) {
  void *ret;

  // TODO: refactor to calloc 
  if (! (ret = malloc(sz)) )
    error("out of memory (while allocating %d bytes)", sz);
  
  memset(ret, 0, sz);
  return ret;
}
