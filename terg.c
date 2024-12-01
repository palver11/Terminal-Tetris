#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "snake.h"
#include "univf.h"


//  NOTE(Pavel): included for testing, delete later
#include <time.h>
static void TESTING_MODE() {
  printf("%d", time(0)*1000);
}

int main() {
  int selected;
  
  puts("\n" "Terminal Games by Palver"
       "\n" "1. Snake"
       "\n" "2. TESTING MODE"
       "\n" "0. Exit"
      );

  // Check if a valid key was pressed
  do {
    selected = (int)getch() - 48; //1-9 is ASCII 48-57
  } while (selected < 0 || selected > 2);

  clear_screen(false);

  switch (selected) {
    case 0:
      return 0;
    case 1:
      game_loop();
      break;
    case 2:
      TESTING_MODE();
      break;
  }

  puts("\n" "Press any key to escape...");
  getch();

  return 0;
}
