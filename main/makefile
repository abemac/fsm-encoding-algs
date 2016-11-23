OBJS = ../encode/Graph.o ../encode/Path.o ../remove_edges/ec.o ../remove_edges/etr.o ../remove_edges/re.o
CC = g++ -std=c++11
DEBUG = -g
LFLAGS = -Wall $(DEBUG)
CFLAGS = $(LFLAGS) -c

output: main.cpp $(OBJS)
		$(CC) $(LFLAGS) main.cpp $(OBJS) -o run
