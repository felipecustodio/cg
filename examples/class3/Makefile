# using gcc compiler
CC = gcc

# output path and filename
BINARY = ./build/output

# sources directory
# SRC = ./examples/sandbox.cpp
# SRC = ./examples/stars.c
# SRC = ./examples/02-02-ExemploTransformacoes2D.c
# SRC = ./examples/exemplo_mouse.cpp

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
