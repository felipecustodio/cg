# using gcc compiler
CC = gcc

# output path and filename
BINARY = ./build/output

# sources directory
SRC = ./src/shapes.c ./src/transforms.c ./src/physics.c ./src/scene.c ./src/main.c

# includes directory
INCLUDES = ./includes

# libraries and flags
LIBS = -lglut -lGL -lGLU -lm
FLAGS = -Wall -O0 -g -Wextra -pthread

all: compile run clean

compile:
	$(CC) -o $(BINARY) -I$(INCLUDES) $(SRC) $(LIBS) $(FLAGS)

test:
	run clean debug

run:
	$(BINARY)

debug:
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes $(BINARY)

clean:
	rm *.o
