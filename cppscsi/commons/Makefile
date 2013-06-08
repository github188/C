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
		 -I$(INCPATH)/login
		
INCDIR  = $(INCPRG)

CFLAGS += $(INCDIR)

#SOURCES:=$(shell find $(ROOTDIR) -name '*.cpp' -o -name '*.c')
SOURCES:=$(shell find $(ROOTDIR) -maxdepth 1 -name '*.cpp' -o -name '*.c')
CPPSRC :=$(notdir $(SOURCES))
OBJECTS:=$(CPPSRC:.cpp=.o)

# search all subdirs
#subdirs := $(sort $(subst /,,$(dir $(wildcard */*))))
subdirs := ./common \
           ./digest \
		   ./data \
		   ./datasegment \
		   ./login

# generate subdirs object name
OBJS_OTHER_SRC := $(shell find $(subdirs) -name '*.cpp')
OBJS_OTHER := $(OBJS_OTHER_SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "**************** build subdir ****************"
	$(foreach N,$(subdirs),make -C $(N);)
	@echo "**************** link target ****************"
	$(CC) -o $(TARGET) $(OBJECTS) $(OBJS_OTHER) $(SHARLIB) $(CFLAGS)

$(OBJECTS): %.o:%.cpp
	$(CC) -c $< $(CFLAGS)

.PHONY: clean
clean:
	$(foreach N,$(subdirs),make -C $(N) clean;)
	rm -f *.o $(TARGET) 
