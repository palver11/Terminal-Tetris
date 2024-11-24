#include <string.h>
#include <stdio.h>

#define F_WIDTH 30  +1 // 1 for NULL
#define F_HEIGHT 30
#define game_field char

static void fill_field(game_field (*f)[F_WIDTH]) {
  char wall_symb = '#';
  char row[2][F_WIDTH]; // row[0] - top and bottom, row[1] - left and right

  // Makes row template
  for (int i = 0; i < (F_WIDTH - 1); i++) {
    if (i == 0 || i == (F_HEIGHT - 1)) {
      row[1][i] = wall_symb;
    } else {
      row[1][i] = ' ';
    }
    row[0][i] = wall_symb; 
  }  
  row[0][F_WIDTH - 1] = '\0';
  row[1][F_WIDTH - 1] = '\0';
  
  // fill the field
  for (int i = 0; i < F_HEIGHT; i++) {
    if (i == 0 || i == (F_HEIGHT - 1)) {
      strcpy(f[i], row[0]);
    } else {
      strcpy(f[i], row[1]);
    }
  }  
}

static void draw_field(game_field (*f)[F_WIDTH]) {
  for (int i = 0; i < F_HEIGHT; i++) {
    puts(f[i]);
  }  
}

// Main loop of the Snake game
int game_loop() {
  game_field field[F_HEIGHT][F_WIDTH];

  fill_field(field);
  draw_field(field);

//printf("%s", field[0]);
  
  return 0;
}
