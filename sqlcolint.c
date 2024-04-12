#include "his.h"

int sqlcolint(SqlCtx_s *ctx, int col) {
  return sqlite3_column_int(ctx->stmt, col);
}
