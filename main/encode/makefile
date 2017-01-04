OBJS = Graph.o Path.o
CC = g++ -std=c++11
DEBUG = -g
LFLAGS = -Wall $(DEBUG)
CFLAGS = $(LFLAGS) -c

all: Graph.o Path.o
Graph.o: Graph.h Graph.cpp
		$(CC) $(CFLAGS) Graph.cpp
Path.o: Path.h Path.cpp
		$(CC) $(CFLAGS) Path.cpp
