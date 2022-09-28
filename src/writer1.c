#include <stdio.h>
#include <logger.h>
#include <time.h>
#include <stdlib.h>

#define process_name "writer1"

int main(){
	init_log();
	char buffer[100];
	for(int i = 0; i < 100; i++){
		sprintf(buffer, "%d -- %d", i, i*i);
		write_to_log(process_name, i%3, buffer);
	}
	close_log();
	return 0;
}

