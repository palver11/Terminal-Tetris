#include <string.h>
#include <stdio.h>
#include <windows.h>

#define F_WIDTH 30  +1 // 1 for NULL
#define F_HEIGHT 30
#define game_field char

// Graphics constants
#define TITLE "Snake Game"
#define WALL_SYMB '#'
#define ARENA_SPACE ' '

static void fill_field(game_field (*f)[F_WIDTH]) {
  char row[2][F_WIDTH]; // row[0] - top and bottom, row[1] - left and right

  // Makes row template
  for (int i = 0; i < (F_WIDTH - 1); i++) {
    if (i == 0 || i == (F_HEIGHT - 1)) {
      row[1][i] = WALL_SYMB;
    } else {
      row[1][i] = ARENA_SPACE;
    }
    row[0][i] = WALL_SYMB; 
  }  
  row[0][F_WIDTH - 1] = '\0';
  row[1][F_WIDTH - 1] = '\0';
  
  // Fill the field
  for (int i = 0; i < F_HEIGHT; i++) {
    if (i == 0 || i == (F_HEIGHT - 1)) {
      strcpy(f[i], row[0]);
    } else {
      strcpy(f[i], row[1]);
    }
  }  
}

static void draw_field(game_field (*f)[F_WIDTH]) {
// NOTE(Pavel): Printing the title as fix of the problem of the terminal consuming top row of the arena
  //Printing Title
  puts("\n" TITLE "\n");

  for (int i = 0; i < F_HEIGHT; i++) {
    puts(f[i]);
  }  
}

// Main loop of the Snake game
int game_loop() {
  // Building visuals
  game_field field[F_HEIGHT][F_WIDTH];

  fill_field(field);

  // Game Loop
  while (1) {
    system("cls");
    draw_field(field);
    Sleep(1000);
  }
  
  return 0;
}
