

all: library program

program:
	$(MAKE) -C ./src
	
library:
	$(MAKE) -C ./lib
