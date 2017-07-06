# using gcc compiler
CC = gcc

# output path and filename
BINARY = ./build/output

# sources directory
SRC = ./src/glsl.c ./src/material.c ./src/obj.c ./src/shapes.c ./src/camera.c ./src/scene.c ./src/main.c
# SOIL sources
SOIL = ./src/SOIL/image_DXT.c ./src/SOIL/image_helper.c ./src/SOIL/stb_image_aug.c ./src/SOIL/SOIL.c
# SDL_mixer sources
SDL_MIXER = ./src/SDL_mixer/dynamic_flac.c ./src/SDL_mixer/dynamic_mp3.c ./src/SDL_mixer/effects_internal.c ./src/SDL_mixer/load_aiff.c ./src/SDL_mixer/load_voc.c ./src/SDL_mixer/music_cmd.c ./src/SDL_mixer/music_mod.c ./src/SDL_mixer/dynamic_fluidsynth.c ./src/SDL_mixer/dynamic_ogg.c ./src/SDL_mixer/effect_stereoreverse.c ./src/SDL_mixer/load_flac.c ./src/SDL_mixer/mixer.c ./src/SDL_mixer/music_flac.c ./src/SDL_mixer/music_modplug.c ./src/SDL_mixer/dynamic_mod.c ./src/SDL_mixer/effect_position.c ./src/SDL_mixer/fluidsynth.c ./src/SDL_mixer/load_ogg.c ./src/SDL_mixer/music.c ./src/SDL_mixer/music_mad.c ./src/SDL_mixer/music_ogg.c ./src/SDL_mixer/wavestream.c

# includes directory
INCLUDES = ./includes
# SOIL includes
SOIL_IN = ./includes/SOIL
# SDL includes
SDL = $(shell sdl-config --cflags --libs)
# SDL mixer includes
SDL_MIXER_IN = ./includes/SDL_mixer

# libraries and flags
LIBS = -lglut -lGL -lGLU -lGLEW -lm
FLAGS = -O0 -g -pthread -lSDLmain -lSDL
GLEW = -lGLEW

all: compile clear run clean

compile:
	$(CC) -o $(BINARY) $(SDL) -I$(SOIL_IN) $(SOIL) -I$(SDL_MIXER_IN) $(SDL_MIXER) -I$(OBJ) -I$(INCLUDES) $(SRC) $(LIBS) $(FLAGS) $(GLEW)

test:
	run clean debug

run:
	$(BINARY)

debug:
	gdb $(BINARY)

clear:
	clear

clean:
	rm *.o
zip:
	zip -r spaceinvaders.zip ../assignment2
