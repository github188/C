###########################################################
# Makefile
#
# History:
# 2013-06-06 Dennis Create
###########################################################

CC= g++

SRC= ByteBuffer.cpp

OBJS := $(SRC:.cpp=.o)

all: $(OBJS)

$(OBJS): %.o:%.cpp
	$(CC) -c $<

.PHONY: clean
clean:
	rm -f *.o 
