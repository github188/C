###########################################################
# Makefile
#
# History:
# 2013-06-05 Dennis Create
###########################################################

CC= g++

SRC= LoginRequestParser.cpp \
     LoginResponseParser.cpp

FLAGS = -I../ -I../common

OBJS := $(SRC:.cpp=.o)

all: $(OBJS)

$(OBJS): %.o:%.cpp
	$(CC) $(FLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o 
