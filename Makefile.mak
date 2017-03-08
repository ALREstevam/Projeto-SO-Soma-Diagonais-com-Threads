CC     = gcc
RM     = rm -f
OBJS   = main.o

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

main.o: main.c matrixDymnAlloc.h
	$(CC) -Wall -s -c $< -o $@ $(CFLAGS)

