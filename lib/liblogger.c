#include "logger.h"

#define log_file_path "./log.db"


int write_to_log(char *process_name, char *message_type, char *message){
	if(access(log_file_path, F_OK) != 0){
		db_setup();
		printf("no file");
	}
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), "INSERT INTO LogMessage (Process, Time,"
		"Type, Message) VALUES ('%s', DATETIME(),"
		" '%s', '%s')",
		process_name, message_type, message);
	return run_single_query(buffer);
}
int read_log(char *name){
	sqlite3 *db;
	sqlite3_stmt *res;
	int rc;
	if(sqlite3_open(log_file_path, &db)){
		fprintf(stderr, "Can't open the database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	char *query = "SELECT * FROM LogMessage ";
	if(name != NULL){
		char filter[100];
		snprintf(filter, sizeof(filter), "WHERE Process = '%s'", name);
		strcat(query, filter);
	}
	char *error = 0;
	rc = sqlite3_exec(db, query, callback, 0, &error);
	if(rc != SQLITE_OK){
		fprintf(stderr, "Failed to select data: %s\n", error);

		sqlite3_free(error);
		sqlite3_close(db);
		
		return 1;
	}
	sqlite3_close(db);
	return 0;
}
int db_setup(){ 
	return run_single_query("CREATE TABLE LogMessage ( ID integer NOT NULL  PRIMARY" 
			" KEY AUTOINCREMENT, Process varchar(50), " 
			" Time datetime, Type varchar(20),  Message varchar(255))");
}

int run_single_query(char *query){
	sqlite3 *db;
	sqlite3_stmt *res;
	int rc;
	if(sqlite3_open(log_file_path, &db)){
		fprintf(stderr, "Can't open the database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	rc = sqlite3_prepare(db, query,
			-1, &res, 0);
	if (rc != SQLITE_OK) {
        
        	fprintf(stderr, "Failed to execute query: %s\n", sqlite3_errmsg(db));
        	sqlite3_close(db);
        	return 1;
	}    
    	sqlite3_step(res);
    
	sqlite3_finalize(res);
	sqlite3_close(db);
	return 0;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName){
	NotUsed = 0;
	if(argc > 4)
        	fprintf(stdout, "%4s %10s %20s %6s %30s\n", argv[0], argv[1], argv[2], argv[3],
        		argv[4]);
    	
    	return 0;
}

