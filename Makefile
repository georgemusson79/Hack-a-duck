MAINDIR = ./src/
UIDIR = ./src/UserInterface/
CXXFLAGS = -std=c++20 -I $(UIDIR) -Wall -Wfatal-errors

vpath %.* $(UIDIR)

# Phoney Targets

all: MainWindow Main

clean:
	rm -rf *.o Main MainWindow

PHONY: clean all

# Executable Files

Main: Main.o
	g++ $(CXXFLAGS) Main.o -o Main

MainWindow: MainWindow.o Button.o Mouse.o
	g++ $(CXXFLAGS) MainWindow.o Button.o Button.o Menu.o -o MainWindow -lSDL2_image -lSDL2_ttf -lSDL2_mixer
# Object FIles

Main.o: $(MAINDIR)main.cpp
	g++ $(CXXFLAGS) -c $(MAINDIR)main.cpp

MainWindow.o: $(UIDIR)MainWindow.cpp $(UIDIR)MainWindow.h
	g++ $(CXXFLAGS) -c $(UIDIR)MainWindow.cpp

Button.o: $(UIDIR)Button.cpp $(UIDIR)Button.h $(UIDIR)Mouse.h $(UIDIR)MainWindow.h
	g++ $(CXXFLAGS) -c $(UIDIR)Button.cpp

Mouse.o: $(UIDIR)Mouse.cpp $(UIDIR)Mouse.h
	g++ $(CXXFLAGS) -c $(UIDIR)Mouse.cpp

Menu.o: $(UIDIR)Menu.cpp $(UIDIR)Menu.h
	g++ $(CXXFLAGS) -c $(UIDIR)Menu.cpp