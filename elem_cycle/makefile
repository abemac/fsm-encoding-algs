
OBJS =
CC = g++ -std=c++11
DEBUG = -g
LFLAGS = -Wall $(DEBUG)
CFLAGS = $(LFLAGS) -c

output: shortest_path/main.cpp $(OBJS)
		$(CC) $(LFLAGS) shortest_path/main.cpp $(OBJS) -o sp
# Graph.o: data_structures/Graph.h data_structures/Graph.cpp
# 		$(CC) $(CFLAGS) data_structures/Graph.cpp
# Path.o: data_structures/Path.h data_structures/Path.cpp
# 		$(CC) $(CFLAGS) data_structures/Path.cpp
