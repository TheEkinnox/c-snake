CC = gcc
FLAGS = -Wall -Wextra -Wshadow
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
EXE_NAME = snake

all: clean build
build : $(OBJ)
	$(CC) $(FLAGS) $^ -o $(EXE_NAME) -lncurses

$(OBJ) : $(SRC)
	$(CC) $(FLAGS) $^ -c

.PHONY: clean
clean :
	rm -rf $(OBJ) $(EXE_NAME)