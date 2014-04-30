###########################################################
# Makefile
# History:
#     2014-04-30  Dennis  Create
###########################################################

CC     = gcc
FLAGS += -Wall -DLINUX
LIBS   = -lpthread -lrt

TARGET = test
OBJ_SRC= test.c mm_pool.c
OBJ_INC=
OBJS  := $(OBJ_SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)

