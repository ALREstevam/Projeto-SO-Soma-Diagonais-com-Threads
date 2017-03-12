CC     = gcc
RM     = rm -f
OBJS   = files/matrixInput.o \
         main.o \
         dataStructures/matrixDymnAlloc.o \
         dataStructures/arrayDymnAlloc.o

LIBS   =
CFLAGS =

.PHONY: projThreads.exe clean clean-after

all: projThreads.exe

clean:
	$(RM) $(OBJS) projThreads.exe

clean-after:
	$(RM) $(OBJS)

projThreads.exe: $(OBJS)
	$(CC) -Wall -s -o $@ $(OBJS) $(LIBS)

files/matrixInput.o: files/matrixInput.c
	$(CC) -Wall -s -c $< -o $@ $(CFLAGS)

main.o: main.c global.h dataStructures/matrixDymnAlloc.h dataStructures/arrayDymnAlloc.h dataStructures/stackDymnAlloc.h
	$(CC) -Wall -s -c $< -o $@ $(CFLAGS)

dataStructures/matrixDymnAlloc.o: dataStructures/matrixDymnAlloc.c global.h dataStructures/arrayDymnAlloc.h
	$(CC) -Wall -s -c $< -o $@ $(CFLAGS)

dataStructures/arrayDymnAlloc.o: dataStructures/arrayDymnAlloc.c global.h
	$(CC) -Wall -s -c $< -o $@ $(CFLAGS)

