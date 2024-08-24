OBJS=build/main.o build/Menu.o build/function_IO.o build/function_stuinfo.o
CFLAGS=-c -Wall -I include
CC=gcc
RM=rm
TARGET=System.exe
HEAD=include/function_IO.h include/Menu.h include/function.h

all:$(TARGET)
$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
build/%.o:src/%.c $(HEAD)
	$(CC) $(CFLAGS) $< -o $@

.PHONY:clean
clean:
	$(RM) -i $(OBJS) $(TARGET) Database.bin

