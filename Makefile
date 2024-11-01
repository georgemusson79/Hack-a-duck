HEADERS = ./src/headers/
MAINDIR = ./src/
BUILDDIR = ./Build/
CXXFLAGS = -std=c++20 -I $(MAINDIR) -I $(HEADERS) -Wall -Wfatal-errors

vpath %.cpp $(MAINDIR)
vpath %.h $(HEADERS)

# Phoney Targets

all: MainWindow Main

clean:
	rm -rf *.o Main

PHONY: clean all

# Executable Files

Main: Main.o
	g++ $(CXXFLAGS) Main.o -o $(BUILDDIR)Main

MainWindow: MainWindow.o
	g++ $(CXXFLAGS) MainWindow.o -o MainWindow
	
# Object FIles

Main.o: main.cpp
	g++ $(CXXFLAGS) -c main.cpp

MainWindow.o: MainWindow.cpp MainWindow.h
	g++ $(CXXFLAGS) -c $(MAINDIR)MainWindow.cpp