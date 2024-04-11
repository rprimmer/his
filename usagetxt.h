/* Auto-generated from usagetxt.txt. Do not edit. */
/* Instead adapt usagetxt.txt and run 'make usagetxt.h' */

#define USAGETEXT \
    "Welcome to his %s, a CLI history tracker and finder of old invocations.\n"\
    "Copyright (c) %s. %s. Distributed under GNU GPL V3.\n"\
    "See %s for more info. Use his as follows:\n"\
    "\n"\
    "his [--flags] [ARGS]\n"\
    "\n"\
    "  Displays history having ARGS or the last entered ones. Use \'what\' to exactly\n"\
    "  match, or \'what%%\' to match anything starting with what, or \'%%what\' for\n"\
    "  anything ending in what, or \'%%what%%\' for whatever has what in it, or \'__at\'\n"\
    "  for anything that is 4 characters long and ends with at.\n"\
    "\n"\
    "  Use flags --first=FROM and --last=TO if you want to time-limit.\n"\
    "  Use flag  --count=NR to limit the displayed entries, default is 20 last.\n"\
    "  Use flag  --utc to output timestamps relative to GMT, default is local.\n"\
    "\n"\
    "his [--flags] -a,--add LINE\n"\
    "  Adds LINE to the history, see --list-formats for the supported parsing\n"\
    "  formats of LINE and --format=X to select a format.\n"\
    "\n"\
    "his [--flags] -i,--import\n"\
    "  Import from stdin in the same format as a listing. Flags --first=FROM and\n"\
    "  --last=TO can be used to limit what to import. Implies --format=2.\n"\
    "  Add flag --utc if the list to import was generated with --utc (recommended).\n"\
    "\n"\
    "his [--flags] -p,--purge\n"\
    "  Remove entries from the database. Flags -f,--first and -l,--last must be\n"\
    "  given to avoid mistakenly removing everything.\n"\
    "\n"\
    "Supported general flags:\n"\
    "  -d,--db=DB                : Sets Sqlite3 database path, default is $HOME/.his.db\n"\
    "  -f,--first=STAMP          : Limits exports and searches to later or equal to\n"\
    "                              STAMP, with STAMP having the format:  YYYY-MM-DD/HH:MM:SS\n"\
    "  -F,--format=FMT           : Sets the format for parsing during --add\n"\
    "  -l,--last=STAMP           : Limits exports and searches to earlier or equal to STAMP\n"\
    "  -L,--list-formats         : Shows available parsing formats and stops\n"\
    "  -m,--multi-args           : During --add, LINE is assumed to to have all args\n"\
    "                            separately (as in ls -Flag). Default is all in one string (as in \'ls -Flag\').\n"\
    "  -R, --report_missing_args : Be verbose when #args is incorrect\n"\
    "  -u,--utc                  : Timestamps in listed output or imported input are assumed UTC (default: local time)\n"\
    "  -v,--verbose              : Increases verbosity\n"\
    "  -h,-?,--help              : Shows this text and stops\n"\
    "  --                        : Stops parsing flags. Very useful in his --add -- $WHATEVER (when $WHATEVER contains a --flag)\n"\
    "\n"
