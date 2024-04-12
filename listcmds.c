#include "his.h"

typedef struct {
  int cmd_id;    /* ID in cmd table */
  int timestamp; /* Timestamp in cmd table */
  int hitcount;  /* Nr. of args this entry matches */
} Result;

/* The invocation was without timestamps, without a count_g, without args, so a
   full dump.  We can just order by timestamp, without constraints, and show all. */
static void list_all() {
  SqlCtx_s *ctx;

  ctx = sqlnew("SELECT cmd_id, timestamp FROM cmd ORDER BY timestamp", 0);
  while ( (sqlrun(ctx) == SQLITE_ROW) )
    show_command(sqlcolint(ctx, 0), sqlcolint(ctx, 1));

  sqlend(ctx);
}

/* The invocation was without args to find, but with a count_g or with
   timestamps. We must order by the timestamp in reverse to get the most recent
   matching entries, and then flip it for display. */
static void list_by_timestamps() {
  SqlCtx_s *ctx;
  char *sql, *extra;
  Result *res = 0;
  int nres = 0, i;

  sql = xstrdup("SELECT cmd_id, timestamp FROM cmd");

  /* Add --first if given */
  if (first_timestamp_g) {
    extra = xsprintf(" WHERE timestamp >= %d", first_timestamp_g);
    sql = xstrcat(sql, extra);
    free(extra);
  }

  /* Add --last if given */
  if (last_timestamp_g) {
    if (first_timestamp_g)
      sql = xstrcat(sql, " AND ");
    else
      sql = xstrcat(sql, " WHERE ");

    extra = xsprintf(" timestamp <= %d", last_timestamp_g);
    sql = xstrcat(sql, extra);
    free(extra);
  }

  /* We need to fetch the last ones and then display them in reverse order. */
  sql = xstrcat(sql, " ORDER BY timestamp DESC");

  /* Add countlimit if given */
  if (count_g) {
    extra = xsprintf(" LIMIT %d", count_g);
    sql = xstrcat(sql, extra);
    free(extra);
  }

  ctx = sqlnew(sql, 0);
  free(sql);

  while ( (sqlrun(ctx) == SQLITE_ROW) ) {
    if (!nres)
      res = (Result *) xcalloc(sizeof(Result));
    else
      res = (Result *) xrealloc(res, (nres + 1) * sizeof(Result));

    res[nres].cmd_id    = sqlcolint(ctx, 0);
    res[nres].timestamp = sqlcolint(ctx, 1);
    nres++;
  }
  sqlend(ctx);

  for (i = nres - 1; i >= 0; i--)
    show_command(res[i].cmd_id, res[i].timestamp);

  free(res);
}

/* qsort callback */
static int compar(const void *a, const void *b) {
  Result *ra = (Result *)a;
  Result *rb = (Result *)b;
  return ra->timestamp - rb->timestamp;
}

/* The invocation was with args to find. */
static void list_with_finding(int ac, char **av) {
  char *full, *sql, *extra, *stamp, *stringop;
  SqlCtx_s *ctx;
  int i, n, found;
  Result *res = 0;
  int nres = 0;

  full = full_command(ac, av);
  LOG_MSG("filtering for [%s]", full);
  free(full);

  for (i = 0; i < ac; i++) {
    /* SQL string operator is '=' unless we have a % or _ in the given name. */
    stringop = strchr(av[i], '%') || strchr(av[i], '_') ? "LIKE" : "=";

    sql = xsprintf("SELECT cmd.cmd_id, cmd.timestamp "
		   "FROM   cmd, crossref, args "
		   "WHERE  cmd.cmd_id = crossref.cmd_id "
		   "AND    crossref.args_id = args.args_id "
		   "AND    args.arg %s ?", stringop);
    if (first_timestamp_g) {
      extra = xsprintf(" AND cmd.timestamp >= %d", first_timestamp_g);
      sql = xstrcat(sql, extra);
      free(extra);
    }
    if (last_timestamp_g) {
      if (first_timestamp_g)
        extra = xsprintf(" AND cmd.timestamp <= %d", last_timestamp_g);

      sql = xstrcat(sql, extra);
      free(extra);
    }
    
    sql = xstrcat(sql, " ORDER BY cmd.timestamp");

    LOG_MSG("looking for [%s]", av[i]);
    ctx = sqlnew(sql, 1, STR, av[i]);
    free(sql);
    
    while (sqlrun(ctx) == SQLITE_ROW) {
      found = 0;
      for (n = 0; n < nres; n++)
        if (res[n].cmd_id    == sqlcolint(ctx, 0) && res[n].timestamp == sqlcolint(ctx, 1)) {
          res[n].hitcount++;
          found++;
        }
      if (!found) {
        res = (Result *) xrealloc(res, (nres + 1) * sizeof(Result));
        res[nres].cmd_id    = sqlcolint(ctx, 0);
        res[nres].timestamp = sqlcolint(ctx, 1);
        res[nres].hitcount = 1;
        nres++;
      }
    }
    for (n = 0; n < nres; n++) {
      stamp = timestamp2str(res[n].timestamp);
      LOG_MSG("ID %d at %s now has %d hits", res[n].cmd_id, stamp, res[n].hitcount);
      free(stamp);
    }
  }

  sqlend(ctx);

  /* Sort the results by timestamp. */
  qsort(res, nres, sizeof(Result), compar);

  // Remove entries that don't hit all required args, ie. entries where hitcount < ac
  n = 0;
  while (n < nres)
    if (res[n].hitcount < ac) {
      memmove(res + n, res + n + 1, (nres - n - 1) * sizeof(Result));
      nres--;
    } else {
      n++;
    }

  /* Display starts at 0 if:
     - There is no count_g specified
     - There is a count_g specified, but we have less hits (nres)
     Else, display starts at nres-count_g
  */
  if (!count_g || nres - count_g <= 0)
    n = 0;
  else
    n = nres - count_g;

  for (; n < nres; n++)
    if (res[n].hitcount == ac)
      show_command(res[n].cmd_id, res[n].timestamp);
  
  free(res);
}

void list_cmds(int ac, char **av) {
  /* If the count_g is uninitialized (-1) then apply the default 20. */
  // TODO: refactor to make count_g a parameter, not a global
  if (count_g < 0)
    count_g = 20;

  if (ac)
    list_with_finding(ac, av);
  else {
    if (first_timestamp_g || last_timestamp_g || count_g)
      list_by_timestamps();
    else
      list_all();
  }
}
