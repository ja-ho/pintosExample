CC = gcc
OBJS = main.o
TARGET = testlib

.SUFFIXES: .c .o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $S $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
