HEADERS = ./headers/
SRCFILES = ./src/
CXXFLAGS = -std=c++20 -I ($HEADERS) -I ($SRCFILES) -Wall -Wfatal-errors

vpath %.h $(HEADERS)
vpah %.cpp $(SRCFILES)

# Phoney Targets

clean:
	rm -rf *.o Main

PHONY: clean all

# Executable Files

Main: Main.o
	g++ ($CXXFLAGS) Main.o -o Main

# Object FIles

Main.o: main.cpp main.h
	g++ ($CXXFLAGS) -c main.cpp main.h