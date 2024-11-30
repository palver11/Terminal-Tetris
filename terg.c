#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "snake.h"

enum GAME_LIST { EXIT, SNAKE };

int main() {
  enum GAME_LIST selected;
  
  puts("\n" "Terminal Game by Palver"
       "\n" "1. Snake"
       "\n" "0. Exit"
      );
  scanf("%d", &selected);
  system("cls");

  switch (selected) {
    case 0:
      return 0;
    case 1:
      game_loop();
      break;
  }

// NOTE(Pavel): test how compiler may know when the array ends,
// make separated assigning if it's possible
// int arr[][10];

  puts("\n" "Press any key to escape...");
  getch();

  return 0;
}
