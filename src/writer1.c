#include <stdio.h>
#include <logger.h>

#define process_name "writer1"

int main(){
	if(write_to_log(process_name, "INFO", "SOMETHING something")){
		printf("KLAIDA!!!!");
	}
	return 0;
}

/*
BEGIN CREATE TABLE"
			"LogMessage"
			"( ID int NOT NULL AUTO_INCREMENT, Time datetime, Type varchar(20),"
			" Message varchar(255)) INSERT INTO Log_Message ( null, GETDATE(), INFO"
			"'Table created') END"
*/
