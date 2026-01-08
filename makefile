CC = g++
CFLAGS = -Wall -O2 $(shell pkg-config --cflags raylib)
LDFLAGS = $(shell pkg-config --libs raylib)

TARGET = main
SRC = main.cpp grid.cpp simulation.cpp

all:
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)
