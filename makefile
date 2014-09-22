CC = g++
CFLAGS = -g -std=c++1y
OBJECTS = build/test.o
TARGET = test


all: build run_tests
build: $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

build/test.o: test.cpp pattern_matching.h tuple.h tuple_private.h
	mkdir -p build
	$(CC) $(CFLAGS) -o build/test.o -c test.cpp

run_tests:
	./test

clean:        
	rm -rf $(TARGET) build/
	