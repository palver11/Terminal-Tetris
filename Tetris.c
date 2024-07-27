#include <stdio.h>
#include <time.h>
#include "figures.h"
#include "termirend.h"

typedef char* string;

int main() {
  int q = 0;
  while (1) {
    wait(2);

    draw_field(CUBE);

    printf("\n%d", ++q);
  }

  printf("\n ** Enter anything and press enter to terminate the program **\n");
  getchar();
  return 0;
}