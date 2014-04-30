###########################################################
# Makefile
# History:
#     2014-04-30  Dennis  Create
###########################################################

CC     = gcc
FLAGS += -Wall

TARGET = mystrace hello
OBJ_SRC= mystrace.c hello.c
OBJS  := $(OBJ_SRC:.c=.o)

all: $(TARGET)

mystrace: mystrace.c
	$(CC) $(FLAGS) -o $@ $^

hello: hello.c
	$(CC) $(FLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)

