
OBJS =ec.o re.o etr.o
CC = g++ -std=c++11
DEBUG = -g
LFLAGS = $(DEBUG)
CFLAGS = $(LFLAGS) -c

output: main.cpp $(OBJS)
		$(CC) $(LFLAGS) main.cpp $(OBJS) -o run
ec.o: ec.h ec.cpp
		$(CC) $(CFLAGS) ec.cpp
re.o: re.h re.cpp
	$(CC) $(CFLAGS) re.cpp
etr.o: etr.h etr.cpp re.h ec.h
	$(CC) $(CFLAGS) etr.cpp
