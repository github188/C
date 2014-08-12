CC = gcc
CFLAGS = -g -Wall
SRC = test.c setproctitle.c
OBJ = $(SRC:.c=.o)
LIB = -lpthread
TARGET = test

all:$(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJ)
