#OBJS specifies which files to compile as part of the project
OBJS = Game.o Main_Menu.o game_mode.o animation.o

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME =game

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

%.o : %.cpp
	$(CC) $< $(CFLAGS) -I./ -c -o $@

clean :
	rm *.o