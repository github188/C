###########################################################
# Makefile
#
# History:
# 2013-06-05 Dennis Create
###########################################################

CC= g++

ROOTDIR	= $(shell pwd)
##SRC:=$(shell find $(ROOTDIR) -name '*.cpp')

SRC= IDigest.cpp \
	 NullDigest.cpp \
     CRC32CDigest.cpp \
     DigestFactory.cpp

OBJS := $(SRC:.cpp=.o)

all: $(OBJS) 

IDigest.o: %.o:%.cpp
	$(CC) -c $<

NullDigest.o: %.o:%.cpp
	$(CC) -c $<

CRC32CDigest.o: %.o:%.cpp
	$(CC) -c $<

DigestFactory.o: %.o:%.cpp
	$(CC) -c $<

.PHONY: clean
clean:
	rm -f *.o 
