CC:=gcc
LIBFOLDER:=/home/studentas/Desktop/3_uzduotis/lib
CFLAGS:=-Wall -I$(LIBFOLDER)
LDFLAGS:=-shared -fPIC
LDLIBS:=-llogger
LDFLAGS:=-L$(LIBFOLDER)
SRC:=$(BIN:.c)
EXTRA:=-Wl,rpath=$(LIBFOLDER)

.PHONY = all clean

all: reader writer1 writer2

reader:reader.c
	$(CC)  -o $@ $^ $(CFLAGS) $(LDLIBS) $(LDLIBS) $(EXTRA)
writer1:writer1.c
	$(CC)  -o $@ $^ $(CFLAGS) $(LDLIBS) $(LDLIBS) $(EXTRA)
writer2:writer2.c
	$(CC)  -o $@ $^ $(CFLAGS) $(LDLIBS) $(LDLIBS) $(EXTRA)

clean:
	rm -f $(BIN)


