CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17
LIBS = $(shell pkg-config --libs raylib)

TARGET = tetris
SRC = main.cpp grid.cpp block.cpp

all:
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LIBS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

