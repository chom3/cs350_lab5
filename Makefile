PROJECT = lab5
TARGET = lab5

SRC_FILES = \
  Makefile \
  lab5.cpp

OBJ_FILES = \
  lab5.o \

CC = g++
CXXFLAGS=-O3 -std=c++0x -pg -D_DEBUG -g -c -Wall

$(TARGET):  	$(OBJ_FILES)
		$(CC) $(OBJ_FILES) -o $@

clean:
		rm -f $(TARGET) *.o *~

lab5.o:		lab5.cpp

