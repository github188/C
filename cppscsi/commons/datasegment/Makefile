CC = g++

ROOTDIR	= $(shell pwd)

INCPATH = $(ROOTDIR)
INCPRG  =-I$(INCPATH) \
         -I$(INCPATH)/../common \
		
INCDIR  = $(INCPRG)

CFLAGS += $(INCDIR)

SOURCES:=$(shell find . -name '*.cpp')
CPPSRC :=$(notdir $(SOURCES))
OBJECTS:=$(CPPSRC:.cpp=.o)

all: $(OBJECTS)

$(OBJECTS): %.o:%.cpp
	$(CC) -c $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o $(TARGET)
