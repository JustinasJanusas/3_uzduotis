
.PHONY = all library program clean_library clean_program

all: library program

library:
	$(MAKE) -C ./lib
	$(MAKE) install -C ./lib

program:
	$(MAKE) -C ./src

clean: clean_library clean_program

clean_library:
	$(MAKE) clean -C ./lib

clean_program:
	$(MAKE) clean -C ./src	

