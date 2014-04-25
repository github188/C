CC     = gcc
CFLAGS = -Wall 
SRC    = netdetect.c
OBJS   = $(SRC:.c=.o)
TARGET = netdetect

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJS)

