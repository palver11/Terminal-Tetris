#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "snake.h"

enum GAME_LIST { EXIT, SNAKE };

int main() {
  enum GAME_LIST selected;
  
  // NOTE(Pavel): MAKE CONFIRMATION WITHOUT ENTER, with getch()?
  puts("\n" "Terminal Game by Palver"
       "\n" "1. Snake"
       "\n" "0. Exit"
      );
  scanf("%d", &selected);
  // NOTE(Pavel): REPLACE WITH clear_screen()
  system("cls");

  switch (selected) {
    case 0:
      return 0;
    case 1:
      game_loop();
      break;
  }

  puts("\n" "Press any key to escape...");
  getch();

  return 0;
}
