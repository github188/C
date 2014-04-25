CC     = gcc
CFLAGS = -Wall 
SRC    = send_arp.c
OBJS   = $(SRC:.c=.o)
TARGET = send_arp

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJS)

