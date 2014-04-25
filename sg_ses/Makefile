CC     = gcc
CFLAGS = -Wall 
SRC    = led_manager.c test_led_manager.c
OBJS   = $(SRC:.c=.o)
TARGET = test_led_manager

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJS)

