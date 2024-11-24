# Define the compiler to use
CC = gcc

# Define any compile-time flags
FLAGS_H = -g -Wall -Wextra -pedantic -std=c11 # Hard flags
FLAGS_E = -g -std=c11 # Easy flags

# Define the source files
SRC = terg.c snake.c

# Define the executable file
EXEC = -o TerminalGames

make:
	gcc $(SRC) $(EXEC) $(FLAGS_E)
