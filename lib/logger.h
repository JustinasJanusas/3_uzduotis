#include <stdio.h>
#include <sqlite3.h>
#include <unistd.h>
#include <string.h>

int write_to_log(char *process_name, char *message_type, char *message);
int read_log(char *name);
int db_setup();
int run_single_query(char *query);
int callback(void *NotUsed, int argc, char **argv, char **azColName);
