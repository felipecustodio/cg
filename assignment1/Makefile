# using gcc compiler
CC = gcc

# output path and filename
BINARY = ./build/output

# sources directory
SRC = ./src/shapes.c ./src/transforms.c ./src/physics.c ./src/scene.c ./src/main.c
# SOIL sources
SOIL = ./src/SOIL/image_DXT.c ./src/SOIL/image_helper.c ./src/SOIL/stb_image_aug.c ./src/SOIL/SOIL.c

# includes directory
INCLUDES = ./includes
# SOIL includes
SOIL_IN = ./includes/SOIL
# SDL includes
SDL = $(shell sdl-config --cflags --libs)

# libraries and flags
LIBS = -lglut -lGL -lGLU -lm
# FLAGS = -Wall -O0 -g -Wextra -pthread
FLAGS = -O0 -g -pthread

all: compile run clean

compile:
	$(CC) -o $(BINARY) $(SDL) -I$(SOIL_IN) $(SOIL) -I$(INCLUDES) $(SRC) $(LIBS) $(FLAGS)

test:
	run clean debug

run:
	$(BINARY)

debug:
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes $(BINARY)

clean:
	rm *.o
