/* Auto-generated from createtablestxt.txt. Do not edit. */
/* Instead adapt createtablestxt.txt and run 'make createtablestxt.h' */

#define CREATETABLESTEXT \
    "CREATE TABLE cmd (\n"\
    "    cmd_id    INTEGER NOT NULL,\n"\
    "    timestamp INTEGER NOT NULL,\n"\
    "    hash      TEXT NOT NULL,\n"\
    "    UNIQUE    (cmd_id, timestamp, hash)\n"\
    ");\n"\
    "CREATE INDEX cmd_id_index           ON cmd(cmd_id);\n"\
    "CREATE INDEX cmd_timestamp_index    ON cmd(timestamp);\n"\
    "CREATE INDEX cmd_id_timestamp_index ON cmd(cmd_id, timestamp);\n"\
    "\n"\
    "CREATE TABLE args (\n"\
    "    args_id INTEGER PRIMARY KEY AUTOINCREMENT,\n"\
    "    arg     TEXT NOT NULL UNIQUE\n"\
    ");\n"\
    "CREATE INDEX args_id_index ON args(args_id);\n"\
    "CREATE INDEX args_arg      ON args(arg);\n"\
    "\n"\
    "CREATE TABLE crossref (\n"\
    "    cmd_id   INTEGER,\n"\
    "    args_id  INTEGER,\n"\
    "    position INTEGER NOT NULL,\n"\
    "    FOREIGN  KEY(cmd_id)  REFERENCES cmd(cmd_id),\n"\
    "    FOREIGN  KEY(args_id) REFERENCES args(args_id)\n"\
    ");\n"\
    "CREATE INDEX crossref_cmd_id_index  ON crossref(cmd_id);\n"\
    "CREATE INDEX crossref_args_id_index ON crossref(args_id);\n"\
    "\n"\
    "CREATE TABLE housekeeping (\n"\
    "    insert_count INTEGER\n"\
    ");\n"\
    "\n"
