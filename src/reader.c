#include <stdio.h>
#include <logger.h>
#include <argp.h>
#include <stdlib.h>


const char *argp_program_version =  "argp-ex3 1.0";
const char *argp_program_bug_address =  "<bug-gnu-utils@gnu.org>";
static char doc[] =
  "reader -- log reader";
static struct argp_option options[] = {
  {"program",  'P', "program_name", 0, "Filter by program" },
  { 0 }
};
struct arguments{
	char *program_name;
};

static error_t parse_opt (int key, char *arg, struct argp_state *state){
	struct arguments *arguments = state->input;
	switch (key){
		
		case 'P':
			arguments->program_name = arg;
			printf("%s\n", arguments->program_name);
			
			
			break;

		default:
			return ARGP_ERR_UNKNOWN;
			
	}
	return 0;
}
static struct argp argp = { options, parse_opt, 0, doc };
int main(int argc, char **argv){
	struct arguments arguments;
	arguments.program_name = NULL;
	argp_parse (&argp, argc, argv, 0, 0, &arguments);
	if(arguments.program_name != NULL)
		return read_log(arguments.program_name);
	return read_log(NULL);
}
