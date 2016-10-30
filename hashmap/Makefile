CC     = gcc
CFLAGS = -Wall -g
SRC    = hash.c
OBJS   = $(SRC:.c=.o)
TARGET = hash

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJS)

