FILES = Tetris.c Figures.c

make: $(FILES)
	gcc $(FILES) -o Tetris

run: Tetris
	./Tetris.exe