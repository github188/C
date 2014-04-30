CC     = gcc
FLAGS  = -Wall
LIBS   = -lpthread
SRC    = main.c mm.c memlib.c csapp.c
OBJS   = $(SRC:.c=.o)
TARGET = main

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LIBS) $(FLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -f $(OBJS) $(TARGET)

