#include "logger.h"

#define LOG_FILE_PATH "/var/log/mylogs.db"

static sqlite3 *db_con = NULL;

static int run_single_query(char *query, int argc, char *argv[])
{
	sqlite3_stmt *res;
	int rc = 0;
	rc = sqlite3_prepare(db_con, query,
			-1, &res, 0);
	if (rc != SQLITE_OK) {
        
        	fprintf(stderr, "Failed to execute query: %s\n", sqlite3_errmsg(db_con));
        	return 1;
	}    
	for(int i = 0; i < argc; i++){
		if(i == 1)
			sqlite3_bind_int(res, i+1, atoi(argv[i]));
		else
			sqlite3_bind_text(res, i+1, argv[i], strlen(argv[i]) , NULL);
	}
	rc = sqlite3_step(res);
	if (rc != SQLITE_OK && rc != SQLITE_DONE)
		return rc;
	sqlite3_clear_bindings(res);
	sqlite3_reset(res);
	sqlite3_finalize(res);	
	return 0;
}

static int db_setup()
{ 
	int rc = 0;
	rc = run_single_query("CREATE TABLE IF NOT EXISTS MessageType ( ID integer NOT NULL " 
			"PRIMARY KEY , Name TEXT(30)); ", 0, NULL);
	if(rc != SQLITE_OK && rc != SQLITE_DONE)
		return rc;
	rc = run_single_query("INSERT or IGNORE INTO  MessageType (ID, Name) VALUES (0, 'INFO'), (1, 'WARNING'), (2, 'ERROR');",
						0, NULL);
	if(rc != SQLITE_OK && rc != SQLITE_DONE)
		return rc;
	rc = run_single_query("CREATE TABLE IF NOT EXISTS LogMessage ( ID integer NOT NULL " 
			"PRIMARY KEY AUTOINCREMENT, Process TEXT(30), " 
			" Time datetime DEFAULT CURRENT_TIMESTAMP, Type integer, "
			" Message TEXT(255), FOREIGN KEY (Type) REFERENCES MessageType(ID)) ;", 0, NULL);
	return 0;
}


int init_log() 
{
	int rc = 0;
	rc = sqlite3_open(LOG_FILE_PATH, &db_con);
	if(rc){
		fprintf(stderr, "Can't open the database: %s\n", sqlite3_errmsg(db_con));
		sqlite3_close(db_con);
		return rc;
	}
	db_setup();
	return rc;
}
int close_log()
{
	sqlite3_close(db_con);
	return 0;
}

int write_to_log(char *process_name, int message_type, char *message)
{
	int rc = 0;

	char buffer[1024];
	char typebuf[3];
	sprintf(typebuf, "%d", message_type);
	snprintf(buffer, sizeof(buffer), "INSERT INTO LogMessage (Process, "
		"Type, Message) VALUES (?, ?, ?)");
	char *args[3] = {process_name, typebuf, message};
	rc = run_single_query(buffer, 3, args);
	return rc;
}

int read_log(char *name)
{
	sqlite3_stmt *res;
	int rc = 0;
	char query[256] = "SELECT LogMessage.ID, LogMessage.Process, LogMessage.Time, "
						"MessageType.Name, LogMessage.Message FROM LogMessage LEFT JOIN"
						" MessageType ON LogMessage.Type = MessageType.ID ";
	if(name != NULL){
		strcat(query, "WHERE LogMessage.Process = ? ;");
	}
	rc = sqlite3_prepare(db_con, query, -1, &res, 0);
	
	if(rc != SQLITE_OK){
		fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db_con));
		return rc;
	}
	if(name != NULL){
		
		rc = sqlite3_bind_text(res, 1, name, strlen(name), NULL);
	}
	rc = sqlite3_step(res);
	while(rc == SQLITE_ROW){
		fprintf(stdout, "%4s %10s %20s %-8s %s\n", sqlite3_column_text(res, 0), 
				sqlite3_column_text(res, 1), sqlite3_column_text(res, 2), 
				sqlite3_column_text(res, 3), sqlite3_column_text(res, 4));
		rc = sqlite3_step(res);
	}
	sqlite3_clear_bindings(res);
	sqlite3_reset(res);
	sqlite3_finalize(res);
	return 0;
}





