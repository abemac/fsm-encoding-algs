
OBJS =ec.o
CC = g++ -std=c++11
DEBUG = -g
LFLAGS = -Wall $(DEBUG)
CFLAGS = $(LFLAGS) -c

output: main.cpp $(OBJS)
		$(CC) $(LFLAGS) main.cpp $(OBJS) -o ec
 ec.o: ec.h ec.cpp
		$(CC) $(CFLAGS) ec.cpp
# Path.o: data_structures/Path.h data_structures/Path.cpp
# 		$(CC) $(CFLAGS) data_structures/Path.cpp
