CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= ./
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=  -lfreeglut -lOpenGl32  -lglu32
# LIBRARIES	:=  -lfreeglut -lopengl32 
# LIBRARIES := -lglut -lGLU -lGL -lglfw
EXECUTABLE	:= main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)
	main.exe
clean:
	-rm $(BIN)/*
