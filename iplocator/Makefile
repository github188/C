########## Makefile ##########
CC=gcc
FLAGS += -Wall

TARGET=bserver bclient
OBJECTS=common.o

all: $(TARGET)

bserver: bserver.o $(OBJECTS)
	$(CC) $(FLAGS) -o bserver bserver.o $(OBJECTS)

bclient: bclient.o $(OBJECTS)
	$(CC) $(FLAGS) -o bclient bclient.o $(OBJECTS)

bserver.o bclient.o common.o: commdef.h common.h

.PHONY: clean
clean:
	rm -f *.o $(TARGET)
