CC     = gcc
CFLAGS = -Wall 
SRC    = sqlite_example.c sqlite_insert.c
OBJS   = $(SRC:.c=.o)
LIB    = -lsqlite3
#if compile c++ code file, or use g++ to compile directory
#LIB   += -l stdc++
TARGET = sqlite_example sqlite_insert

all:$(TARGET)

#$(TARGET):$(OBJS)
#	$(CC) $(CFLAGS) $(LIB) -o $@ $^

sqlite_example:sqlite_example.c
	$(CC) $(CFLAGS) $(LIB) -o $@ $^

sqlite_insert:sqlite_insert.c
	$(CC) $(CFLAGS) $(LIB) -o $@ $^


.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJS)

