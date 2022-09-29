CC:=gcc
CFLAGS:=-Wall 
LDFLAGS:=-shared -fPIC
LIB:=liblogger.so
PREFIX:=/usr
LDLIBS:=-lsqlite3

.PHONY = all install uninstall clean

all: $(LIB)

$(LIB): liblogger.c
	$(CC) $(CFLAGS) $(LDFLAGS)  -o $@ $^ $(LDLIBS)

install: $(LIB)
	install -d $(PREFIX)/include
	install -m 644 logger.h $(PREFIX)/include/logger.h
	install -d $(PREFIX)/lib
	install -m 644 $(LIB) $(PREFIX)/lib/
uninstall:
	$(RM) $(PREFIX)/include/logger.h
	$(RM) $(PREFIX)/lib/$(LIB) 
clean:
	rm -f $(LIB)


