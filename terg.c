#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "snake.h"
#include "univf.h"

int main() {
  int selected;
  
  puts("\n" "Terminal Games by Palver"
       "\n" "1. Snake"
       "\n" "0. Exit"
      );

  // Check if a valid key was pressed
  do {
    selected = (int)getch() - 48; //1-9 is ASCII 48-57
  } while (selected < 0 || selected > 1);

  clear_screen(false);

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
