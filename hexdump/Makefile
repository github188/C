CC     = gcc
CFLAGS = -Wall 
SRC    = hexdump.c
OBJS   = $(SRC:.c=.o)
TARGET = myhexdump

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJS)

