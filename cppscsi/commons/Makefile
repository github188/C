###########################################################
# Makefile
#
# History:
# 2013-06-03 Dennis Create
# 2013-06-04 Dennis Make it correct and better
###########################################################

.SUFFIXES : .x .o .c .cpp .s
ROOTDIR	= $(shell pwd)

CC = g++

TARGET = cppscsi

#LIBDIR	= $(ROOTDIR)/lib
#SHARLIB:=$(shell find $(LIBDIR) -name '*.so')

INCPATH = $(ROOTDIR)
INCPRG  =-I$(INCPATH) \
         -I$(INCPATH)/common \
         -I$(INCPATH)/digest \
		
INCDIR  = $(INCPRG)

CFLAGS += $(INCDIR)

SOURCES:=$(shell find $(ROOTDIR) -name '*.cpp' -o -name '*.c')
CPPSRC :=$(notdir $(SOURCES))
OBJECTS:=$(CPPSRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(SHARLIB)

$(OBJECTS):
	$(CC) $(CFLAGS) -c $< $(SOURCES)

.PHONY: clean
clean:
	rm -f *.o $(TARGET)
