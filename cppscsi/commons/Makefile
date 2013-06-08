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
		 -I$(INCPATH)/datasegment \
		
INCDIR  = $(INCPRG)

CFLAGS += $(INCDIR)

#SOURCES:=$(shell find $(ROOTDIR) -name '*.cpp' -o -name '*.c')
SOURCES:=$(shell find $(ROOTDIR) -maxdepth 1 -name '*.cpp' -o -name '*.c')
CPPSRC :=$(notdir $(SOURCES))
OBJECTS:=$(CPPSRC:.cpp=.o)
OBJS_OTHER := ./common/ByteBuffer.o \
              ./digest/IDigest.o \
			  ./digest/DigestFactory.o \
			  ./digest/NullDigest.o \
			  ./digest/CRC32CDigest.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(OBJS_OTHER) $(SHARLIB) $(CFLAGS)

$(OBJECTS): %.o:%.cpp
	$(CC) -c $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o $(TARGET) $(OBJS_OTHER)
