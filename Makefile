#!/usr/bin/env make


CC = gcc 
CFLAGS = -O1
LDFLAGS = # 

all: build run 

TARGET = ./main
SOURCES = ./main.c


build: $(TARGET)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SOURCES)

OUTCOPY = out.txt

run: build
	$(TARGET) | tee $(OUTCOPY) 

clean:
	rm -f $(TARGET)
	rm -f *.o *~


