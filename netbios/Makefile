CC     = gcc
CFLAGS = -Wall 
SRC    = netbios.c
OBJS   = $(SRC:.c=.o)
TARGET = netbios

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJS)

