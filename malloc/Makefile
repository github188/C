CC     = gcc
FLAGS  = -Wall
SRC    = main.c mm.c
OBJS   = $(SRC:.c=.o)
TARGET = main

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -f $(OBJS) $(TARGET)

