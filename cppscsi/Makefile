###########################################################
# Makefile
# History:
# 2013-06-03 Dennis Create
###########################################################


CC   = g++
FLAG = -Wall
LIBS = 

TARGET = cppscsi
SRC    = test.cpp \
         BasicHeaderSegment.cpp AdditionalHeaderSegment.cpp \
         ProtocolDataUnit.cpp ProtocolDataUnitFactory.cpp 
OBJS  := $(SRC:.cpp=.o) 


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAG) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	rm -f *.o $(TARGET)
