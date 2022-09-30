CC:=gcc
LIBFOLDER:=../lib
CFLAGS:=-Wall -I$(LIBFOLDER)
LDFLAGS:=-shared -fPIC
LDLIBS:=-llogger
LDFLAGS:=-L$(LIBFOLDER)
BIN:=reader writer1 writer2
EXTRA:=-Wl,-rpath=$(LIBFOLDER)

.PHONY = all clean

all: $(BIN)

reader:reader.c
	$(CC)  -o $@ $^ $(CFLAGS) $(LDLIBS) $(EXTRA)
writer1:writer1.c
	$(CC)  -o $@ $^ $(CFLAGS) $(LDLIBS) $(EXTRA)
writer2:writer2.c
	$(CC)  -o $@ $^ $(CFLAGS) $(LDLIBS) $(EXTRA)

clean:
	rm -f $(BIN)


