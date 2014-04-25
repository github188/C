CC     = gcc
CFLAGS = -Wall 
SRC    = dowall.c w2tty.c
OBJS   = $(SRC:.c=.o)
TARGET = w2tty 

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJS)

