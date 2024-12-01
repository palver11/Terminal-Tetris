#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <conio.h>
#include "univf.h"


// Misc Consts
#define DELAY 1000/10 // ms | 1sec/fps
#define VECZERO {0, 0}

// Graphics constants
#define TITLE "Snake Game"
#define SYMB_WALL '#'
#define SYMB_SPACE ' '
#define SNAKE_HEAD '0'
#define SNAKE_BODY 'X'
#define FOOD '*'

// Game constants
#define F_WIDTH (60 + 1) // 1 for NULL
#define F_HEIGHT 30

#define START_POS {F_WIDTH / 2, F_HEIGHT / 2}

// Enums
enum movement {
  UP, DOWN, LEFT, RIGHT, IDLE
};

// Custom Types
typedef char game_field;
typedef struct vector {
  int x;
  int y;
} vector;

// Global variables
char GAME_OVER[F_HEIGHT][F_WIDTH];

// FUNCTIONS
static void fill_field(game_field (*f)[F_WIDTH]) {
  char row[2][F_WIDTH]; // row[0] - top and bottom, row[1] - left and right

  // Makes row template
  for (int i = 0; i < (F_WIDTH - 1); i++) {
    if (i == 0 || i == (F_WIDTH - 2)) {
      row[1][i] = SYMB_WALL;
    } else {
      row[1][i] = SYMB_SPACE;
    }
    row[0][i] = SYMB_WALL; 
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

static void fill_gameover(game_field (*f)[F_WIDTH]) {
  const char SCORE[3][17] = {
    "   GAME OVER!   ",
    "                ",
    " score:         "
  };
  char wall_row[F_WIDTH];

  for (int i = 0; i < (F_WIDTH - 1); i++) {
    wall_row[i] = SYMB_WALL;
  }  
  for (int i = 0; i < F_HEIGHT; i++) {
    strcpy(f[i], wall_row);
  }  

  int first_line = (F_HEIGHT / 2) - 2;
  for (int fi = (F_WIDTH / 2) - ((17 - 1) / 2), i = 0; i < (17 - 1); fi++, i++) {
    f[first_line][fi] = SCORE[1][i];
    f[first_line+1][fi] = SCORE[0][i];
    f[first_line+2][fi] = SCORE[1][i];
    f[first_line+4][fi] = SCORE[2][i];
  }  
}

static void place_snake(game_field (*f)[F_WIDTH], vector h_pos) {
  f[h_pos.y][h_pos.x] = SNAKE_HEAD;
}

static void move_snake(vector *v, int direction) {
  if ((v->x) < (F_WIDTH - 1) &&
      (v->x) > 0 &&
      (v->y) < (F_HEIGHT) &&
      (v->y) > 0
      ) {
    switch (direction) {
      case 0: // UP
        v->y--;
        break;
      case 1: // DOWN
        v->y++;
        break;
      case 2: // LEFT
        v->x--;
        break;
      case 3: // RIGHT
        v->x++;
        break;
//    default:
        
    }
  }
}

static void draw_game(game_field (*f)[F_WIDTH]) {
  clear_screen(true);
  //Printing Title
  puts("\n" TITLE "\n");

  for (int i = 0; i < F_HEIGHT; i++) {
    puts(f[i]);
  }  
}

static void check_input(enum movement *move_dir) {
  if (GetAsyncKeyState('W') & 0x8000) {
    *move_dir = UP;
  }
  else if (GetAsyncKeyState('S') & 0x8000) {
    *move_dir = DOWN;
  }
  else if (GetAsyncKeyState('A') & 0x8000) {
    *move_dir = LEFT;
  }
  else if (GetAsyncKeyState('D') & 0x8000) {
    *move_dir = RIGHT;
  }
}

// MAIN LOOP OF THE SNAKE GAME
int game_loop() {
  enum movement move_direction = IDLE;
  vector snake_head_pos = START_POS;
  char input;

  // Building visuals
  game_field field[F_HEIGHT][F_WIDTH];
  game_field game_over[F_HEIGHT][F_WIDTH];

  // Game Loop
  while (true) {

    fill_field(field);
    fill_gameover(game_over);
    move_snake(&snake_head_pos, move_direction);
    place_snake(field, snake_head_pos);
    check_input(&move_direction);
    draw_game(field);

    //Game over condition
    //Checks if the snake has hit a wall
    if (snake_head_pos.x == 0 || 
        snake_head_pos.y == 0 || 
        snake_head_pos.x == (F_WIDTH - 2) ||
        snake_head_pos.y == (F_HEIGHT - 1)
        ) {
      break;
    }

    Sleep(DELAY);
  }

  draw_game(game_over);
  puts("\n" "Press any key to escape...");
  getch();
  
  return 0;
}
