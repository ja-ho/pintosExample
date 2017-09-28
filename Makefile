CC = gcc
CFLAGS = -Wall -g
SUBOBJS = list.o hash.o bitmap.o
OBJS = main.o $(SUBOBJS)
SRCS = main.c bitmap.c hash.c list.c
TARGET = testlib

.SUFFIXES: .c .o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)

list.o : list.c list.h
hash.o : hash.c hash.h
bitmap.o : bitmap.c bitmap.h limits.h round.h stdio.c
main.o : main.c $(SUBOBJS)
