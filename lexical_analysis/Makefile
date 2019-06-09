CC		:= g++
C_FLAGS := -std=c++17 -Wall -Wextra  -g -DDEBUG

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
LIBNAME := token


LIBRARIES	:=

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
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) -shared -fPIC  $(filter-out %/main.cc,$^)  -o $(BIN)/$(LIBNAME).so

$(BIN)/$(EXECUTABLE): $(SRC)/*
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)
