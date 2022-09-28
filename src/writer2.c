#include <stdio.h>
#include <logger.h>

int main(int argc, char *argv[]){
	int rc = 0;
	rc = init_log();
	if(rc)
		return rc;
		
	rc = write_to_log(argv[0], "ERROR", "IT PRINTS!");
	close_log();
	return rc;
}
