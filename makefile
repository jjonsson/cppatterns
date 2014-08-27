CC = g++
CFLAGS = -g -std=c++11
OBJECTS = build/patterns.o
TARGET = patterns


all: build
build: $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

build/patterns.o: patterns.cpp
	mkdir -p build
	$(CC) $(CFLAGS) -o build/patterns.o -c patterns.cpp

clean:        
	rm -rf $(TARGET) build/