CC = gcc
FLAGS = -Wall -Wextra -Wshadow -lncurses
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
EXE_NAME = snake

all: clean build
build : $(OBJ)
	$(CC) $^ $(FLAGS) -o $(EXE_NAME)

$(OBJ) : $(SRC)
	$(CC) $^ $(FLAGS) -c

.PHONY: clean
clean :
	rm -rf $(OBJ) $(EXE_NAME)