###########################################################
# Makefile
#
# History:
# 2013-06-05 Dennis Create
###########################################################

CC= g++

SRC= IDigest.cpp \
     NullDigest.cpp \
     CRC32CDigest.cpp \
     DigestFactory.cpp

OBJS := $(SRC:.cpp=.o)

all: $(OBJS)

$(OBJS): %.o:%.cpp
	$(CC) -c $<

.PHONY: clean
clean:
	rm -f *.o 
