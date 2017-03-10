CC     = gcc
RM     = rm -f
OBJS   = main.o

LIBS   =
CFLAGS = -Wall -g -std=c99 -Werror -pthread

.PHONY: PthreadTest.exe clean clean-after

all: PthreadTest.exe

clean:
	$(RM) $(OBJS) PthreadTest.exe

clean-after:
	$(RM) $(OBJS)

PthreadTest.exe: $(OBJS)
	$(CC) -Wall -s -o $@ $(OBJS) $(LIBS)

main.o: main.c
	$(CC) -Wall -s -c $< -o $@ $(CFLAGS)

