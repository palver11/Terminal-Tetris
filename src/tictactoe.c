#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "inc/tictactoe.h"
#include "inc/univf.h"


int is_gameover(char *data) {
  bool gameover = true;

  // Check if there is a line up formed
  char winner = 'N';
  for (int i = 0; i < 2; i++) {
    char c = (i == 0) ? 'X' : 'O';
    // am I yandare dev? :O
    if ((data[0] == c && data[3] == c && data[6] == c) ||
        (data[1] == c && data[4] == c && data[7] == c) ||
        (data[2] == c && data[5] == c && data[8] == c) ||
        (data[0] == c && data[1] == c && data[2] == c) ||
        (data[3] == c && data[4] == c && data[5] == c) ||
        (data[6] == c && data[7] == c && data[8] == c) ||
        (data[0] == c && data[4] == c && data[8] == c) ||
        (data[2] == c && data[4] == c && data[6] == c)) {
      winner = c;
    }
  }  
  if (winner == 'X' || winner == 'O') { gameover = true; }

  if (gameover && winner != 'N') {
    puts("\nGAME OVER"); 
    printf("\n= The winner: %c =\n", winner);
    return 1;
  }

  // Check if there is a free spot left
  for (int i = 0; i < 9; i++) {
    if (data[i] == ' ') {
      gameover = false;
    }
  }

  if (gameover) {
    puts("\nGAME OVER"
         "\n= Draw =\n"); 
    return 1;
  } else { return 0; }
}

void draw_game(char *data) {
    clear_screen(false);
    puts("\nTIC|TAC|TOE\n");
    // Draw graphics
    printf("%c|%c|%c\n"
           "------\n"
           "%c|%c|%c\n"
           "------\n"
           "%c|%c|%c\n",
           data[0], data[1], data[2], 
           data[3], data[4], data[5], 
           data[6], data[7], data[8]);
}

void ttt_game_loop () {
  char data[10] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
  char selection;
  int game_timer = 4;
  bool player_turn_first;

  srand(time(0));

  player_turn_first = rand() % 2;
  

  while (true) {
    draw_game(data);
    
    if (is_gameover(data)) {break;}

    // Player's turn
    if (player_turn_first) {
      puts("Your turn: ");
      while (true) {
        selection = getch();
        switch (selection) {
          case 'q': 
            if (data[0] == ' ') {
              data[0] = 'X';
              break;
            } else { continue; }
          case 'w': 
            if (data[1] == ' ') {
              data[1] = 'X';
              break;
            } else { continue; }
          case 'e': 
            if (data[2] == ' ') {
              data[2] = 'X';
              break;
            } else { continue; }
          case 'a': 
            if (data[3] == ' ') {
              data[3] = 'X';
              break;
            } else { continue; }
          case 's': 
            if (data[4] == ' ') {
              data[4] = 'X';
              break;
            } else { continue; }
          case 'd': 
            if (data[5] == ' ') {
              data[5] = 'X';
              break;
            } else { continue; }
          case 'z': 
            if (data[6] == ' ') {
              data[6] = 'X';
              break;
            } else { continue; }
          case 'x': 
            if (data[7] == ' ') {
              data[7] = 'X';
              break;
            } else { continue; }
          case 'c': 
            if (data[8] == ' ') {
              data[8] = 'X';
              break;
            } else { continue; }
          default:
            continue;
        }
        break;
      }
    }

    draw_game(data);
    if (is_gameover(data)) {break;}

    // Comp turn
    while (true) {
      int rand_indx = rand() % 9;
      if (data[rand_indx] == ' ') {
        data[rand_indx] = 'O';
        player_turn_first = true;
        break;
      }
    }

    game_timer--;
  }

  getch();
}
