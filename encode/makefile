OBJS = Graph.o Path.o
CC = g++ -std=c++11
DEBUG = -g
LFLAGS = -Wall $(DEBUG)
CFLAGS = $(LFLAGS) -c

# output: main.cpp $(OBJS)
# 		$(CC) $(LFLAGS) main.cpp $(OBJS) -o run
Graph.o: Graph.h Graph.cpp
		$(CC) $(CFLAGS) Graph.cpp
Path.o: Path.h Path.cpp
		$(CC) $(CFLAGS) Path.cpp
