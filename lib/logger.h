#include <stdio.h>
#include <sqlite3.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


enum type_m {INFO = 0, WARNING = 1, ERROR = 2};

int write_to_log(char *process_name, int message_type, char *message);
int read_log(char *name);
int close_log();
int init_log();

