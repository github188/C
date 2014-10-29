CC     = gcc
CFLAGS = -Wall -g2
LIB_CPP= -lstdc++

TARGET = t1 t2 t3

all:$(TARGET)

t1: t1.c
	$(CC) $(FLAGS) -o $@ $^

t2: t2.c
	$(CC) $(FLAGS) -o $@ $^

t3: t3.cpp
	$(CC) $(FLAGS) $(LIB_CPP) -o $@ $^

.PHONY:clean
clean:
	rm -f *.o $(TARGET)
