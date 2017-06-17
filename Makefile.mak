CC     = gcc
RM     = rm -f
OBJS   = main.o \
         Thread/thread.o \
         Thread/callThread.o \
         File/fileMngr.o \
         dataStructures/Matrix/matrixMngr.o \
         dataStructures/Array/arrayMngr.o \
         Util/util.o

LIBS   = -lpthread
CFLAGS =

.PHONY: projso.exe clean clean-after

all: projso.exe

clean:
	$(RM) $(OBJS) projso.exe

clean-after:
	$(RM) $(OBJS)

projso.exe: $(OBJS)
	$(CC) -Wall -s -o $@ $(OBJS) $(LIBS)

main.o: main.c Util/util.h datadefine.h dataStructures/Array/arrayMngr.h dataStructures/Matrix/matrixMngr.h Thread/thread.h File/fileMngr.h Thread/callThread.h
	$(CC) -Wall -s -c $< -o $@ $(CFLAGS)

Thread/thread.o: Thread/thread.c Thread/thread.h Util/util.h datadefine.h dataStructures/Matrix/matrixMngr.h dataStructures/Array/arrayMngr.h
	$(CC) -Wall -s -c $< -o $@ $(CFLAGS)

Thread/callThread.o: Thread/callThread.c Thread/thread.h Util/util.h datadefine.h dataStructures/Array/arrayMngr.h dataStructures/Matrix/matrixMngr.h File/fileMngr.h
	$(CC) -Wall -s -c $< -o $@ $(CFLAGS)

File/fileMngr.o: File/fileMngr.c datadefine.h dataStructures/Matrix/matrixMngr.h
	$(CC) -Wall -s -c $< -o $@ $(CFLAGS)

dataStructures/Matrix/matrixMngr.o: dataStructures/Matrix/matrixMngr.c datadefine.h
	$(CC) -Wall -s -c $< -o $@ $(CFLAGS)

dataStructures/Array/arrayMngr.o: dataStructures/Array/arrayMngr.c datadefine.h
	$(CC) -Wall -s -c $< -o $@ $(CFLAGS)

Util/util.o: Util/util.c datadefine.h File/fileMngr.h
	$(CC) -Wall -s -c $< -o $@ $(CFLAGS)

