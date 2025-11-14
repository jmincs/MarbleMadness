CC = g++
STD = -std=c++17

SDL2_CFLAGS := $(shell pkg-config --cflags sdl2 SDL2_image SDL2_mixer SDL2_ttf 2>/dev/null)
SDL2_LIBS := $(shell pkg-config --libs sdl2 SDL2_image SDL2_mixer SDL2_ttf 2>/dev/null)

OPENGL_CFLAGS = -I/System/Library/Frameworks/OpenGL.framework/Headers -DGL_SILENCE_DEPRECATION
OPENGL_LIBS = -framework OpenGL -framework GLUT

INCLUDES = $(SDL2_CFLAGS) $(OPENGL_CFLAGS)
LIBS = $(SDL2_LIBS) $(OPENGL_LIBS)

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.h)

.PHONY: default all clean

PRODUCT = MarbleMadness

all: $(PRODUCT)

%.o: %.cpp $(HEADERS)
	@$(CC) -c $(STD) $(CCFLAGS) $(INCLUDES) $< -o $@

$(PRODUCT): $(OBJECTS) 
	@$(CC) $(OBJECTS) $(LIBS) -o $@

clean:
	rm -f *.o
	rm -f $(PRODUCT)
