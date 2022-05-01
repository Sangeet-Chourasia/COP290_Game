#OBJS specifies which files to compile as part of the project
OBJS = Game.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME =game

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

#output: game.o Main_Menu.o
#	g++ main.o  window.o  rect.o  -o  output $(LINKER_FLAGS) 

#main_menu.o : Main_Menu.cpp Main_Menu.h globals.h
#	g++ main.cpp -c $(COMPILER_FLAGS) 

#game.o: game.cpp globals.h
#	g++ -c window.cpp $(COMPILER_FLAGS)
