#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <assert.h>
#include <conio.h>


// Misc Consts
#define DELAY 1000/30 // ms | 1sec/fps
#define VECZERO {0, 0}

// Graphics constants
#define TITLE "Snake Game"
#define WALL_SYMB '#'
#define ARENA_SPACE ' '
#define SNAKE_HEAD '0'
#define SNAKE_BODY 'X'
#define FOOD '*'

// Game constants
#define F_WIDTH 60  +1 // 1 for NULL
#define F_HEIGHT 30

#define START_POS {15, 15}

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

char GAME_OVER[F_HEIGHT][F_WIDTH];

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

static void place_snake(game_field (*f)[F_WIDTH], vector h_pos) {
  f[h_pos.y][h_pos.x] = SNAKE_HEAD;
}

static void move_snake(vector *v, int direction) {
  if ((v->x + 1) < (F_WIDTH - 1) &&
      (v->x + 1) > 0 &&
      (v->y + 1) < (F_HEIGHT- 1) &&
      (v->y + 1) > 0
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

static void draw_field(game_field (*f)[F_WIDTH]) {
  //Printing Title
  puts("\n" TITLE "\n");

  for (int i = 0; i < F_HEIGHT; i++) {
    puts(f[i]);
  }  
}

// MAIN LOOP OF THE SNAKE GAME
int game_loop() {
  bool Playing = true;
  enum movement move_direction = IDLE;
  vector snake_head_pos = START_POS;
  char input;

  // Building visuals
  game_field field[F_HEIGHT][F_WIDTH];

  // Game Loop
  while (Playing) {
    system("cls");

    fill_field(field);
    place_snake(field, snake_head_pos);
    move_snake(&snake_head_pos, move_direction);

    if (_kbhit()) {
      input = _getch();
      switch (input) {
        case 'w':
          move_direction = UP;
          break;
        case 's':
          move_direction = DOWN;
          break;
        case 'a':
          move_direction = LEFT;
          break;
        case 'd':
          move_direction = RIGHT;
          break;
      }
    }

    draw_field(field);
    //Check if the snake has hit a wall
    if (snake_head_pos.x == 0 || 
        snake_head_pos.y == 0 || 
        snake_head_pos.x == (F_WIDTH - 2) ||
        snake_head_pos.y == (F_HEIGHT - 1)
        ) {
      Playing = false;
      system("cls");
      draw_field(GAME_OVER);
//    puts("\nGAME OVER!");
    }

    Sleep(DELAY);
  }
  
  return 0;
}

// MORE GRAPHICS

char GAME_OVER[F_HEIGHT][F_WIDTH] = {
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "#######                #######",
  "#######   GAME OVER!   #######",
  "#######                #######",
  "##############################",
  "####### score:         #######",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
  "##############################",
};
