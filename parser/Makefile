CC		:= g++
C_FLAGS := -std=c++17 -Wall -Wextra -g

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
LIBNAME := token

LIBRARIES	:= lib/token.so

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
else
EXECUTABLE	:= main
endif

all: $(BIN)/$(EXECUTABLE)

clean:
	$(RM) $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)
lib: $(SRC)/*
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $(filter-out %/main.cc,$^) -o lib$(LIBNAME)

$(BIN)/$(EXECUTABLE): $(SRC)/*
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)