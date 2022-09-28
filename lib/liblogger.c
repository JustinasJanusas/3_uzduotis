#include "logger.h"

#define log_file_path "./log.db"

static sqlite3 *db_con = NULL;
static int run_single_query(char *query, int argc, char *argv[]){
	sqlite3_stmt *res;
	int rc = 0;
	rc = sqlite3_prepare(db_con, query,
			-1, &res, 0);
	if (rc != SQLITE_OK) {
        
        	fprintf(stderr, "Failed to execute query: %s\n", sqlite3_errmsg(db_con));
        	return 1;
	}    
	for(int i = 0; i < argc; i++){
		sqlite3_bind_text(res, i+1, argv[i], 30, NULL);
	}
    	rc = sqlite3_step(res);
	sqlite3_finalize(res);	
	return rc;
}

static int db_setup(){ 
	int rc = 0;
	rc = run_single_query("CREATE TABLE IF NOT EXISTS LogMessage ( ID integer NOT NULL " 
			"PRIMARY" 
			" KEY AUTOINCREMENT, Process varchar(50), " 
			" Time datetime DEFAULT CURRENT_TIMESTAMP, Type varchar(20), "
			" Message varchar(255));", 0, NULL);
	return rc;
}


static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	NotUsed = 0;
	if(argc > 4)
        	fprintf(stdout, "%4s %10s %20s %6s %30s\n", argv[0], argv[1], argv[2], argv[3],
        		argv[4]);
    	return 0;
}

int init_log() {
	int rc = 0;
	rc = sqlite3_open(log_file_path, &db_con);
	if(rc){
		fprintf(stderr, "Can't open the database: %s\n", sqlite3_errmsg(db_con));
		sqlite3_close(db_con);
		return rc;
	}
	db_setup();
	return rc;
}
int close_log(){
	sqlite3_close(db_con);
	return 0;
}

int write_to_log(char *process_name, char *message_type, char *message){
	int rc = 0;

	char buffer[1024];
	snprintf(buffer, sizeof(buffer), "INSERT INTO LogMessage (Process, "
		"Type, Message) VALUES (?, ?, ?)");
	char *args[3] = {process_name, message_type, message};
	rc = run_single_query(buffer, 3, args);
	return rc;
}

int read_log(char *name){
	sqlite3_stmt *res;
	int rc = 0;
	char query[256] = "SELECT * FROM LogMessage ";
	if(name != NULL){
		char filter[128];
		snprintf(filter, sizeof(filter), "WHERE Process = '%s';", name);
		strcat(query, filter);
	}
	char *error = 0;
	rc = sqlite3_exec(db_con, query, callback, 0, &error);
	if(rc != SQLITE_OK){
		fprintf(stderr, "Failed to select data: %s\n", error);

		sqlite3_free(error);
		sqlite3_close(db_con);
		
		return 1;
	}
	sqlite3_close(db_con);
	return 0;
}





