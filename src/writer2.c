#include <stdio.h>
#include <logger.h>
#include <signal.h>
#include <time.h>

#define process_name "writer2"

void sig_handler(int sig_num)
{
	if(sig_num == SIGINT){
		close_log();
		exit(1);
	}
}

int main(int argc, char *argv[])
{
	int rc = 0;
	rc = init_log();
	if(rc)
		return rc;
	int type;
	char buffer[100];
	int i = 0;
	while(i < 10){
		int start_time = clock();
		while(clock() < start_time + 1000000);
		type = rand() % 3;
		sprintf(buffer, "lucky number is! %d", rand());
		rc = write_to_log("writer2", type, buffer);
		if(rc)
			break;
		i++;
	}
	close_log();
	return rc;
}

