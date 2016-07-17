CC     = gcc
CFLAGS += -g -Wall
SRC    = $(wildcard *.c)
OBJS   = $(SRC:.c=.o)
#BINS   = $(SRC:.c=)
TARGET = test
LIBS   =

all:$(TARGET)

# bin files depend on *.c files
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

.PHONY: clean
clean:
	rm -f *.o $(TARGET)
