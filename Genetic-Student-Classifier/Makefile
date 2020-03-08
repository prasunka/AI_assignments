CC = g++

CFLAGS = -g -Wall -lm

TARGET = student-classifier

all : $(TARGET)

$(TARGET) : classifier-genetic.o classifier-tool.o
	$(CC) $(CFLAGS) -o $(TARGET) classifier-genetic.o classifier-tool.o
	$(RM) *.o
classifier-gen.o : classifier-genetic.cpp classifier_gen.h
	$(CC) $(CFLAGS) -c classifier-genetic.cpp

tool.o : classifier-tool.cpp classifier_gen.h
	$(CC) $(CFLAGS) -c classifier-tool.cpp
clean :
	$(RM) $(TARGET) *.o *~