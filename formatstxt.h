/* Auto-generated from formatstxt.txt. Do not edit. */
/* Instead adapt formatstxt.txt and run 'make formatstxt.h' */

#define FORMATSTEXT \
    "Available formats are identified by a number. Available are:\n"\
    "\n"\
    "--format=1, -F1:\n"\
    "  Selects a format where a history number (unused), a datestamp, and a command\n"\
    "  are present. Example:\n"\
    "    2087  [2017-08-22 13:57:32 +0200] ls -ltr /tmp\n"\
    "  This is the format for the bash expression \'$(history 1)\' once you\n"\
    "  set\n"\
    "    export HISTTIMEFORMAT=\"[%%Y-%%m-%%d %%H:%%M:%%S %%z] \"\n"\
    "  which is recommended -- it makes your Bash builtin command \'history\' behave\n"\
    "  much nicer and \'his\' will understand it by default.\n"\
    "\n"\
    "  The leading number (2087) is a byproduct of bash and is unused. The datestamp\n"\
    "  is spread out over two or three parts and must follow the syntax (including\n"\
    "  the shown square brackets):\n"\
    "    [YYYY-MM-DD HH:MM:SS]         (this is assumed UTC) or\n"\
    "    [YYYY-MM-DD HH:MM:SS +/-HHMM] (this is assumed localtime, with offset to\n"\
    "                                   UTC)\n"\
    "\n"\
    "--format=2, -F2:\n"\
    "  Selects the format that is also used during listing and during --import:\n"\
    "  a local-time date/time and the command. With flag --utc this is UTC. Example:\n"\
    "    2017-08-15/05:33:47 cat /tmp/myfile.c\n"\
    "\n"\
    "--format=3, -F3:\n"\
    "  Selects a format where a Unix timestamp (seconds since 1970-01-01, UTC) is\n"\
    "  followed by any arguments. This is handy when you can get a $(time +%%s) in\n"\
    "  but it\'s least human-readable of the formats. Example:\n"\
    "    1503505272 find /var/log -type f -name apache*\n"\
    "\n"\
    "More formats are not supported at this time.\n"\
    "\n"
