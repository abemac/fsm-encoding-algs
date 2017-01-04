
OBJS =ec.o re.o etr.o
CC = g++ -std=c++11
DEBUG = -g
LFLAGS = $(DEBUG)
CFLAGS = $(LFLAGS) -c

all: ec.o re.o etr.o
ec.o: ec.h ec.cpp
		$(CC) $(CFLAGS) ec.cpp
re.o: re.h re.cpp
	$(CC) $(CFLAGS) re.cpp
etr.o: etr.h etr.cpp re.h ec.h
	$(CC) $(CFLAGS) etr.cpp
