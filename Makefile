##OBJS specifies which files to compile as part of the project
#OBJS = main.cpp
#
##OBJ_NAME specifies the name of our exectuable
#OBJ_NAME = main
#
#CC = g++
#
#COMPILER_FLAGS = -Wall
#
#LINKER_FLAGS = -lSDL2
#
##This is the target that compiles our executable
#all : $(OBJS)
#	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
#
CXX = clang++
CXXFLAGS = -Wall
LDLIBS = -lSDL2

