OBJS=build/main.o build/func.o build/Menu.o
CFLAGS=-c -Wall -I include
CC=gcc
RM=rm 
TARGET=bin/System
HEAD=include/function.h include/Menu.h

all:$(TARGET)
$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

build/%.o: src/%.c $(HEAD)
	$(CC) $(CFLAGS) $< -o $@

.PHONY:clean
clean:
	$(RM) $(OBJS) $(TARGET)