#include <stdio.h>
#include <logger.h>
#include <argp.h>


const char *argp_program_version =
  "argp-ex3 1.0";
const char *argp_program_bug_address =
  "<bug-gnu-utils@gnu.org>";
static char doc[] =
  "reader -- log reader";
  static char args_doc[] = "";
static struct argp_option options[] = {
  {"program",  'P', "program_name", OPTION_ARG_OPTIONAL, "Filter by program" },
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
			break;
		case ARGP_KEY_ARG:
			if (state->arg_num >= 1)
			/* Too many arguments. */
				argp_usage (state);


			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}
static struct argp argp = { options, parse_opt, args_doc, doc };
int main(int argc, char **argv){
	struct arguments arguments;
	arguments.program_name = NULL;
	argp_parse (&argp, argc, argv, 0, 0, &arguments);
	if(arguments.program_name != NULL)
		return read_log(arguments.program_name);
	return read_log(NULL);
}
