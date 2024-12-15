#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "inc/snake.h"
#include "inc/univf.h"
#include "inc/tictactoe.h"


//  NOTE(Pavel): included for testing, delete later
#include <time.h>
static void TESTING_MODE() {
  printf("%lld", time(0)*1000);
}

int main() {
  int selected;
  
  while (true) {
    clear_screen(false);

    puts("\n" "Terminal Games by Palver"
         "\n" "1. Snake"
         "\n" "2. Tic Tac Toe"
         "\n" "3. TESTING MODE"
         "\n" "0. Exit"
        );

    // Check if a valid key was pressed
    do {
      selected = (int)getch() - 48; //1-9 is ASCII 48-57
    } while (selected < 0 || selected > 3);

    switch (selected) {
      case 0:
        return 0;
      case 1:
        snake_game_loop();
        break;
      case 2:
        ttt_game_loop();
        break;
      case 3:
        TESTING_MODE();
        break;
    }

  //  puts("\n" "Press any key to escape...");
  //  system("pause");
  }

  return 0;
}
