CC = g++

ROOTDIR	= $(shell pwd)

INCPATH = $(ROOTDIR)
INCPRG  =-I$(INCPATH) \
         -I$(INCPATH)/../common \
		
INCDIR  = $(INCPRG)

CFLAGS += $(INCDIR)

CPPSRC :=$(wildcard  ./*.cpp)
OBJECTS:=$(CPPSRC:.cpp=.o)

all: $(OBJECTS)

#all: 
#	@echo $(OBJECTS)

$(OBJECTS): %.o:%.cpp
	$(CC) -c $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o $(TARGET)
