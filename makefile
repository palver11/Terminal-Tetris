# Define the compiler to use
CC = gcc

# Define any compile-time flags
FLAGS_H = -g -Wall -Wextra -pedantic -std=c11 # Hard flags
FLAGS_E = -g -std=c11 -Wall # Easy flags

# Define the source files
SRC = src/terg.c src/univf.c src/snake.c src/tictactoe.c

# Define the executable file
EXEC = -o TerminalGames

make:
	gcc $(SRC) $(EXEC) $(FLAGS_E)

