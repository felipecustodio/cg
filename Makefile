# using gcc compiler
CC = gcc

# output path and filename
BINARY = ./build/output

# sources directory
SRC = ./src/sandbox.cpp

# includes directory
INCLUDES = ./includes

# libraries and flags
LIBS = -lglut -lGL -lGLU -lm
FLAGS = -Wall -O0 -g -Wextra -pthread

all: compile run clean

compile:
	$(CC) -o $(BINARY) -I$(INCLUDES) $(SRC) $(LIBS)

test:
	run clean debug

run:
	clear && $(BINARY)

debug:
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes $(BINARY)

clean:
	rm *.o
