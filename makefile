# Define the compiler to use
CC = gcc

# Define any compile-time flags
CFLAGS = -g -Wall -Wextra -pedantic -std=c11

# Define the source files
SRC = tetris.c termirend.c figures.c

# Define the executable file
EXEC = Tetris

# The default target to build the executable
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

# Rule to run the program
run: $(EXEC)
	./$(EXEC)

# Rule to clean up generated files
clean:
	rm -f $(EXEC)

# Rule to rebuild the program
rebuild: clean all