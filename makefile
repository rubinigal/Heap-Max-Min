CC = gcc
CFLAGS = -ansi -Wall -pedantic 

all: HeapMaxMin

HeapMaxMin: HeapMaxMin.o HeapTools.o
	$(CC) $(CFLAGS) -o HeapMaxMin HeapTools.o HeapMaxMin.o -lm

HeapMaxMin.o: HeapMaxMin.c header.h
	$(CC) $(CFLAGS) -c HeapMaxMin.c 

HeapTools.o: HeapTools.c header.h
	$(CC) $(CFLAGS) -c HeapTools.c 