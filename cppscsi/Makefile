###########################################################
# Makefile
# History:
# 2013-06-03 Dennis Create
###########################################################


CC    = g++
FLAGS = -Wall
LIBS  = 

TARGET = cppscsi
OBJ_SRC= test.cpp \
         ByteBuffer.cpp \
		 IDigest.cpp \
		 DigestFactory.cpp \
         BasicHeaderSegment.cpp \
         ProtocolDataUnit.cpp \
		 ProtocolDataUnitFactory.cpp
INC    = -I./ -I./common -I./digest
OBJS  := $(OBJ_SRC:.cpp=.o) 


all: $(TARGET)

$(TARGET): $(OBJS)
	@echo $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ $(LIBS) $(INC)

# Using condition compile: make SPECIAL=1
ifeq ($(SPECIAL), 1) 

test.o: test.cpp
	@echo "do cc test"
	$(CC) $(FLAGS) -c $^ $(INC)

ByteBuffer.o: ./common/ByteBuffer.cpp
	@echo "do cc ByteBuffer"
	$(CC) $(FLAGS) -c $^ $(INC)

IDigest.o: ./digest/IDigest.cpp
	@echo "do cc IDigest"
	$(CC) $(FLAGS) -c $^ $(INC)

DigestFactory.o: ./digest/DigestFactory.cpp
	@echo "do cc IDigestFactory"
	$(CC) $(FLAGS) -c $^ $(INC)

BasicHeaderSegment.o: %.o: %.cpp
	@echo "do cc BasicHeaderSegment"
	$(CC) $(FLAGS) -c $^ $(INC)

ProtocolDataUnit.o: %.o: %.cpp
	@echo "do cc ProtocolDataUnit"
	$(CC) $(FLAGS) -c $^ $(INC)

ProtocolDataUnitFactory.o: %.o: %.cpp
	@echo "do cc ProtocolDataUnitFactory"
	$(CC) $(FLAGS) -c $^ $(INC)

else

#$(OBJS): $(OBJ_SRC)
$(OBJS): %.o: %.cpp
	@echo "call here"
	$(CC) $(FLAGS) -c $^

endif

.PHONY: clean
clean:
	rm -f *.o $(TARGET)
