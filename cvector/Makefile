CC     = g++
FLAGS  = -Wall
SRC    = vector.cpp
OBJS   = $(SRC:.cpp=.o)
TARGET = vector

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJS)

