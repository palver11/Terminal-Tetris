# Define the compiler to use
CC = gcc

# Define any compile-time flags
CFLAGS = -g -Wall -Wextra -pedantic -std=c11

# Define the source files
SRC = terg.c snake.c

# Define the executable file
EXEC = -o TerminalGames

make:
	gcc $(SRC) $(EXEC) $(CFLAGS)
