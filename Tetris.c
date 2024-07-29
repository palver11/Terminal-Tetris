#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "figures.h"
// #include "termirend.h"

typedef char* string;

int fps = 3;

int main() {
  while (1) {
    usleep(1000000 / fps);
    system("cls");

    draw_element(GAME_FIELD);
  }

  printf("\n ** Enter anything and press enter to terminate the program **\n");
  getchar();
  return 0;
}

