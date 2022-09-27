#include <stdio.h>
#include <logger.h>
#include <time.h>
#include <stdlib.h>

#define process_name "writer1"

int main(){
	clock_t start_time;
	while(1){
		start_time = clock();
		while(clock() < start_time + 10);
		write_to_log(process_name, "INFO", "TIMER ENDED");
	}
	return 0;
}

