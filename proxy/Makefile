CC     = gcc
CFLAGS = -Wall 
SRC    = proxy.c
OBJS   = $(SRC:.c=.o)
TARGET = proxy

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJS)

