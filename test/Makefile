CC     = gcc
CFLAGS = -Wall 
SRC    = trim_bank.c
OBJS   = $(SRC:.c=.o)
TARGET = trim_bank

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJS)

