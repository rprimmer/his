#include "his.h"

char const *sqlcolstring(SqlCtx_s *ctx, int col) {
  return (char const *) sqlite3_column_text(ctx->stmt, col);
}
