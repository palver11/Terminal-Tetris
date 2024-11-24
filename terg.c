#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "snake.h"


int main() {
//system("cls");
  game_loop();

// NOTE(Pavel): test how compiler may know when the array ends,
// make separated assigning if it's possible
// int arr[][10];

  puts("\n" "Press any key to end...");
  getch();

  return 0;
}
