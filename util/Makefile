###########################################################
# Makefile
# History:
#     2013-09-03  Dennis  Create
###########################################################

CC     = gcc
FLAGS += -Wall -DLINUX

TARGET = test
OBJ_SRC= test.c util.c
OBJ_INC=
OBJS  := $(OBJ_SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ 

# Using condition compile: make SPECIAL=1
ifeq ($(SPECIAL), 1) 

test.o: test.c
	$(CC) $(FLAGS) -c $^

else

$(OBJS): %.o: %.c
	$(CC) $(FLAGS) -c $^

endif	

.PHONY: clean
clean:
	rm -f *.o $(TARGET)

