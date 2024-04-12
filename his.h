/*
 * Central include file for his
 */

#include <getopt.h>
#include <libgen.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sqlite3.h>

// #define HANDLE_ERROR(fmt, ...) handleError(true, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_MSG(fmt, ...) msg(__FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

/* Type for a parsed command to add. */
typedef struct {
  time_t timestamp;
  char *hash;
  int ac;
  char **av;
} CmdToAdd_s;

/* Representation of argc/argv, when parsed from a string. */
typedef struct {
  int argc;
  char **argv;
} Args_s;

/* Type of bindings in a sqlnew() call */
typedef enum {
  INT,
  STR,
} SqlBindType_s;

/* Context for sqlite3 runs */
typedef struct {
  char const *sql;
  sqlite3_stmt *stmt;
} SqlCtx_s;

/* Max parsing format_g that is acceptable and the default */
#define DEFAULT_FORMAT 1
#define MAX_FORMAT     3

/* Data declarations or definitions */
#ifdef DEFINE_DATA
#  define EXTERN
#else
#  define EXTERN extern
#endif

EXTERN char *db;                  /* Database name */

// TODO: see what globals can be done away with entirely
// INFO: refactored globals to have _g suffix 
EXTERN int count_g;               /* Number of entries during recent listing */
EXTERN int accept_his_g;          /* Also add cmds that start with 'his' */
EXTERN sqlite3 *dbconn_g;         /* Database connection */
EXTERN time_t first_timestamp_g;  /* First timestamps when searching/dumping */
EXTERN time_t last_timestamp_g;   /* Last timestamps when searching/dumping */
EXTERN int format_g;              /* Selected format_g */
EXTERN int insert_count_g;        /* number of inserts in the db, 0 if no inserts in run */
EXTERN int multiargs_g;           /* --add should expect multi-args */
EXTERN int report_missing_args_g; /* show error msg when #args is bad */
EXTERN int utc_time_g;            /* List or import timestamps are UTC */
EXTERN int verbose_g;             /* Verbosity or not */

// TODO: move these to their own TU and add doxygen
extern void add(int ac, char **av);
extern void db_cleanup(void);
extern void error(char const *fmt, ...);
extern void list_cmds(int ac, char **av);
extern void find(int ac, char **av);
extern char *full_command(int ac, char **av);
extern time_t gm_mktime(struct tm *t);
extern char *hash_string(char const *s);
extern void import_cmds(void);
extern void list_formats(void);
extern int lookup_arg(char const *arg);
// extern void msg(char const *fmt, ...);
void msg(char *file, const char *func, int line, const char *fmt, ...);
extern void parse(int ac, char **av, CmdToAdd_s *cmd);
extern void purge(void);
extern void show_command(int cmd_id, int timestamp);
extern void str2args(char *s, Args_s *args);
extern time_t str2timestamp(char const *s);
extern void sqlinit(void);
extern int sqlcolint(SqlCtx_s *ctx, int col);
extern const char *sqlcolstring(SqlCtx_s *ctx, int col);
extern SqlCtx_s *sqlnew(char const *sql, int nbindings, ...);
extern int sqlrun(SqlCtx_s *ctx);
extern void sqlend(SqlCtx_s *ctx);
extern char *timestamp2str(time_t t);
extern void usage(void);
extern void *xmalloc(size_t sz);
extern void *xrealloc(void *what, size_t sz);
extern char *xsprintf(char const *fmt, ...);
extern char *xstrcat(char *what, char const *extra);
extern char *xstrdup(char const *what);
