CC:=gcc
CFLAGS:=-Wall 
LDFLAGS:=-shared -fPIC
LIB:=liblogger.so
PREFIX:=/usr
LDLIBS:=-lsqlite3

.PHONY = all install uninstall clean

all: $(LIB)

$(LIB): liblogger.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@ $^

install: $(LIB)
	install -d $(PREFIX)/include
	install -m 644 logger.h $(PREFIX)/include/logger.h

uninstall:
	$(RM) $(PREFIX)/include/logger.h 
clean:
	rm -f $(LIB)


