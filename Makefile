

all: library program

library:
	$(MAKE) -C ./lib

program:
	$(MAKE) -C ./src
	

