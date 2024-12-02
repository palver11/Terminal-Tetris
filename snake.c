#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <conio.h>
#include <time.h>
#include "univf.h"


// Misc Consts
#define DELAY 1000/10 // ms | 1sec/fps
#define VECZERO {0, 0}
#define FOOD_INDENT 3

// Graphics constants
#define TITLE "Snake Game"
#define SYMB_WALL '#'
#define SYMB_SPACE ' '
#define SNAKE_BODY 'O'
#define FOOD '+'

// Game constants
#define F_WIDTH (60 + 1) // 1 for NULL
#define F_HEIGHT 30 

#define START_POS {F_WIDTH / 2, F_HEIGHT / 2, -1, -1, NULL}
#define SNAKE_INIT_LEN 4

// Enums
enum movement {UP, DOWN, LEFT, RIGHT, IDLE};

// Custom Types
typedef char game_field;
typedef struct vector {int x, y;} vector;
typedef struct snake_node {
  int x, y, prev_x, prev_y; 
  struct snake_node *next;
} llist_snake;

// Global variables
char GAME_OVER[F_HEIGHT][F_WIDTH];

// FUNCTIONS
static void fill_field(game_field (*f)[F_WIDTH]) {
  char row[2][F_WIDTH]; // row[0] - top and bottom, row[1] - left and right

  // Makes the row template
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
  
  // Fill the game field
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
//    f[first_line+4][fi] = SCORE[2][i];
  }  
}

static void place_snake(game_field (*f)[F_WIDTH], llist_snake *s) {
  // Place the head
    f[s->y][s->x] = SNAKE_BODY;
  // Place the tail
  while (s->next != NULL) { 
    s = s->next;
    f[s->y][s->x] = SNAKE_BODY;
  }
}

static void move_snake(llist_snake *s, int direction) {
  // Move the head
  if ((s->x) < (F_WIDTH - 1) &&
      (s->x) > 0 &&
      (s->y) < (F_HEIGHT) &&
      (s->y) > 0) {
    // save old coordinates
    s->prev_y = s->y;
    s->prev_x = s->x;
    // move
    switch (direction) {
      case 0: // UP
        s->y--;
        break;
      case 1: // DOWN
        s->y++;
        break;
      case 2: // LEFT
        s->x--;
        break;
      case 3: // RIGHT
        s->x++;
        break;
    }
    // Move the tail
    while (s->next != NULL) {
      //save old coorinates
      s->next->prev_x = s->next->x;
      s->next->prev_y = s->next->y;
      //move
      s->next->x = s->prev_x;
      s->next->y = s->prev_y;
      //change node
      s = s->next;
    }    
  }
}

//  NOTE(Pavel): make safe-check to prevent food spawning on the snake
static void place_food(bool *consumed, vector *f_pos, game_field (*f)[F_WIDTH], llist_snake *s) {
  if (*consumed) { // set new position
    vector pos = {-1, -1};
    
    // Randomize X and Y positions
    do { // X
      pos.x = rand();
    } while (pos.x > (F_WIDTH - 2 - FOOD_INDENT) || pos.x < (1 + FOOD_INDENT));
    do { // Y
      pos.y = rand();
    } while (pos.y > (F_HEIGHT - 1 - FOOD_INDENT) || pos.y < (1 + FOOD_INDENT));

    f_pos->x = pos.x;
    f_pos->y = pos.y;

    *consumed = false;
  }
  
  f[f_pos->y][f_pos->x] = FOOD;
}

static void snake_eat_food(bool *consumed, llist_snake *s) {
  *consumed = true;
  llist_snake *node = malloc(sizeof(llist_snake)); 

  // get the last part of the snake
  while (s->next != NULL) {
    s = s->next;
  }

//  NOTE(Pavel): do I need prev or currient pos? what will come first?  
  node->x      = s->prev_x;
  node->y      = s->prev_y;
  node->prev_x = -1;
  node->prev_y = -1;
  node->next   = NULL;
  s->next    = node;
}

static void draw_game(game_field (*f)[F_WIDTH], int *score) {
  clear_screen(true);
  //Printing Title
  puts("\n" TITLE "\n");
  printf("\nScore: %d\n", *score );

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

static void grow_snake(llist_snake *s, int s_init_len) {
  llist_snake *tmp = s;
  for (int i = 0; i < 10; i++) {
    llist_snake *node = malloc(sizeof(llist_snake));
    node->x = tmp->x;
    node->y = tmp->y+1;
    node->prev_x = -1;
    node->prev_y = -1;
    node->next = NULL;
    s->next = node;
    tmp = node;
  }  
}

// MAIN LOOP OF THE SNAKE GAME
int game_loop() {
  enum movement move_direction = IDLE;
  llist_snake snake = START_POS;
  vector food_pos = {-1, -1};
  bool food_consumed = true;
  int food_score = 0;

  srand(time(0));
  grow_snake(&snake, SNAKE_INIT_LEN);

  // Building visuals
  game_field scrn_field[F_HEIGHT][F_WIDTH];
  game_field scrn_game_over[F_HEIGHT][F_WIDTH];

  // Game Loop
  while (true) {

    fill_field(scrn_field);
    fill_gameover(scrn_game_over);
    move_snake(&snake, move_direction);
    place_food(&food_consumed, &food_pos, scrn_field, &snake);
    place_snake(scrn_field, &snake);
    check_input(&move_direction);

    if (snake.x == food_pos.x && snake.y == food_pos.y) {
      snake_eat_food(&food_consumed, &snake);
      food_score++;
    }

    //Game over conditions
    //If the snake has hit a wall
    if (snake.x == 0 || 
        snake.y == 0 || 
        snake.x == (F_WIDTH - 2) ||
        snake.y == (F_HEIGHT - 1)
        ) {
      break;
    }
    //If the snake has hit yourself
    if (snake.next != NULL) {
      llist_snake *tmp = snake.next;
      bool is_game_over = false;

      while (true) {
        if (snake.x == tmp->x && snake.y == tmp->y) {
          is_game_over = true;
          break;
        } else if (tmp->next != NULL) {
          tmp = tmp->next;
        } else {break;}
      }
      if (is_game_over) {break;}
    }
    draw_game(scrn_field, &food_score);
    Sleep(DELAY);
  }

  draw_game(scrn_game_over, &food_score);
  puts("\n" "Press any key to escape...");
//  NOTE(Pavel): WHY IT CLOSES?  
  getch();
  getch();
  getch();
  getch();
  getch();
  
  return 0;
}
