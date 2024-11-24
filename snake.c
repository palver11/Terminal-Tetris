#include <string.h>
#include <stdio.h>

#define F_WIDTH 30
#define F_HEIGHT 30
#define game_field char

static void fill_field(game_field** f) {
  int f_len = sizeof(f);
  char symb = ' ';
  char row[F_WIDTH];

  // makes row template
  for (int i = 0; i < (F_WIDTH - 1); i++) {
    row[i] = symb;
  }  
  row[F_WIDTH - 1] = '\0';
  
  // fill the field
  for (int i = 0; i < f_len; i++) {
    strcpy(f[i], row);
  }  
}

static void draw_field(game_field** f) {
  for (int i = 0; i < F_HEIGHT; i++) {
    puts(f[i][i]);
  }  
}

// Main loop of the Snake game
int game_loop() {
  game_field[F_WIDTH][F_HEIGHT] field;

  fill_field(&field);
  draw_field(&field);
  
  return 0;
}
