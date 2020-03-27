CC=g++
CFLAGS=-std=c++11 -c -g -Wall
SOURCES=$(wildcard *.cc) $(wildcard *.h)
OBJECTS=$(SOURCES:.cc=.o)

all: $(SOURCES) $(OBJECTS)

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS)
