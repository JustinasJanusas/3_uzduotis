#include <stdio.h>
#include <sqlite3.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define INFO 0
#define WARNING 1
#define ERROR 2



int write_to_log(char *process_name, char *message_type, char *message);
int read_log(char *name);
int close_log();
int init_log();
//int read_log(struct arguments argss);

